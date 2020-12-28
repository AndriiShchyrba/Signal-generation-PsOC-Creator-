// Додавання необхідних бібліотек
#include "project.h"
#include "math.h"

// ================================================================================
// Ініціалізація голобальних змінних
uint8 F = 200, C0 = 127, A = 127, N = 20, iDacValue = 0, RunStatus = 0, Fmod;
uint32 Fhclk = 24000000, Flclk = 32000, TimerCounter = 0, MainTimPer, DurationTimPer;
double T, dt, Amod = 0.2;

// ================================================================================
// Функцї для генерації сигналу шляхом переривання
void SampleGen()
{
    TimerCounter++;          
    
    if (RunStatus == 0)
    {
        //Сигнал в стаціонарному режимі
        iDacValue = C0 + round(A * sin(2 * M_PI * TimerCounter / N)); 
    } 
    else
    {
        //Сигнал в режимі запуску
        iDacValue = C0 + round(A * (0.5 + Amod * sin(2 * M_PI * TimerCounter * dt * Fmod)) * sin(2 * M_PI * TimerCounter / N));        
    }
 
    IDAC_SetValue(iDacValue);  
}

// ================================================================================
// Функція для запуску генерації шляхом переривання
void StartGen()
{
    LCD_Position(1u,7u);
    LCD_PrintString("Run     ");
    RunStatus = 1;
    LED_STATUS_Write(RunStatus);
    
    TimerCounter = 0;    
    TimerDuration_Start(); 
}

// ================================================================================
// Функція для зупинки генерації  шляхом переривання
void StopGen()
{
    TimerDuration_Stop();
    
    LCD_Position(1u,7u);
    LCD_PrintString("Stationary");
    RunStatus = 0;
    LED_STATUS_Write(RunStatus);  
}

// ================================================================================
// Головна функція
int main(void)
{
    CyGlobalIntEnable; /* Увімкнути глобальні переривання. */
    
    // Відображення даних про програму на LCD
    LCD_Start();
    LCD_Position(0u,0u);
    LCD_PrintString("Signal - AM");
    
    LCD_Position(1u,0u);
    LCD_PrintString("Mode");
    
    // Обчислення
    T = 1.0 / F;      // Період
    dt = T / N;     // Час між відліками
    MainTimPer = round(dt / (1.0 / Fhclk)); // Період таймера для налаштування //віліків 
   
    
    IDAC_Start();
    IDAC_SetValue(iDacValue);
    
    // Оголошення функції переривання
    ISR_Start_StartEx(StartGen);
    ISR_NextSamples_StartEx(SampleGen);
    ISR_StopSamples_StartEx(StopGen);
    
    TimerMain_Start();
    TimerMain_WritePeriod(MainTimPer);
    
    for(;;)
    {
        
        // Зчитування стану кнопки
        if (!Pin_Mod_Read())
        {
            //* Якщо Mode 1
            
            Fmod = round(0.2 * F); 
                                   
            LCD_Position(1u,5u);
            LCD_PrintString("1");
            LED_MOD1_Write(1);
            LED_MOD2_Write(0); 
        }
        else
        {
            //* Якщо Mode 2
                        
            Fmod = round(0.1 * F);
            
            LCD_Position(1u,5u);
            LCD_PrintString("2");
            LED_MOD1_Write(0);
            LED_MOD2_Write(1);
        }
        
    }
}
