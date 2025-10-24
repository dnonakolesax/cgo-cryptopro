#include "go_asm.h"
#include "textflag.h"

// func Call1ArgNoResult(function unsafe.Pointer, arg1 uintptr) uint
TEXT ·Call1ArgNoResult(SB), NOSPLIT, $0-16
    // Загружаем аргументы
    MOVQ    function+0(FP), AX   // указатель на функцию
    MOVQ    arg1+8(FP), DI       // 1-й аргумент
    
    // Сохраняем текущий стек
    MOVQ    SP, BX               // BX = оригинальный SP
    
    // Получаем g0
    MOVQ    g, CX                // CX = текущая g
    MOVQ    g_m(CX), CX          // CX = m
    MOVQ    m_g0(CX), DX         // DX = g0
    
    // Переключаемся на стек g0
    MOVQ    (g_sched+gobuf_sp)(DX), SP  // SP = g0.stack
    
    // Выравниваем стек (16-байтное выравнивание для AMD64)
    ANDQ    $~15, SP
    
    // Вызываем функцию
    CALL    AX
    
    // Восстанавливаем оригинальный стек
    MOVQ    BX, SP
    
    RET

// func Call2Args(function unsafe.Pointer, arg1 uintptr, arg2 uintptr, result uintptr) uint
TEXT ·Call2Args(SB), NOSPLIT, $0-32
    // Загружаем аргументы
    MOVQ    function+0(FP), AX   // указатель на функцию
    MOVQ    arg1+8(FP), DI       // 1-й аргумент 
    MOVQ    arg2+16(FP), SI       // 2-й аргумент
    MOVQ    result+24(FP), DX    // 3-й аргумент
    
    // Сохраняем текущий стек
    MOVQ    SP, BX               // BX = оригинальный SP
    
    // Получаем g0
    MOVQ    g, CX                // CX = текущая g
    MOVQ    g_m(CX), CX          // CX = m
    MOVQ    m_g0(CX), R8         // R8 = g0
    
    // Переключаемся на стек g0
    MOVQ    (g_sched+gobuf_sp)(R8), SP  // SP = g0.stack
    
    // Выравниваем стек (16-байтное выравнивание для AMD64)
    ANDQ    $~15, SP
    
    // Вызываем функцию
    CALL    AX
    
    // Восстанавливаем оригинальный стек
    MOVQ    BX, SP

    // Возвращаем результат
    MOVQ    AX, ret+32(FP)
    
    RET
