package casm

import (
	"unsafe"
)

func Call1ArgNoResult(function unsafe.Pointer, arg1 uintptr)
func Call2Args(function unsafe.Pointer, arg1 uintptr, arg2 uintptr, result uintptr) uint32
