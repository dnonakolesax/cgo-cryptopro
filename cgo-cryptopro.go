package ccp

import (
	"fmt"
	"unsafe"

	"github.com/dnonakolesax/cgo-cryptopro/casm"
)

/*
#cgo CFLAGS: -I/opt/cprocsp/include/ -I/opt/cprocsp/include/cpcsp -I/opt/cprocsp/include/pki -Iclib/include
#cgo LDFLAGS: -L/root/ccp/clib/build -lcryptopro
#include "cryptopro.h"
*/
import "C"

type CProError struct {
	Code uint32
}

func (ce *CProError) Error() string {
	if ce.Code <= 0x80000000 {
		return fmt.Sprintf("CryptoPro error: 0x%08d", ce.Code)
	}
	return fmt.Sprintf("CryptoPro error: 0x%08x", ce.Code)
}

func AcquireContext(contName string, contPass string) (uintptr, error) {
	var result = struct {
		provider uintptr
	}{0}
	cont := []byte(contName)
	cont = append(cont, 0)
	pass := []byte(contPass)
	pass = append(pass, 0)

	code := casm.Call2Args(C.acquire_provider, uintptr(unsafe.Pointer(&cont[0])),
		uintptr(unsafe.Pointer(&pass[0])), uintptr(unsafe.Pointer(&result)))

	if code != 0 {
		return 0, &CProError{Code: code}
	}
	return result.provider, nil
}

func SignData(provider uintptr, data string) ([]byte, error) {
	dt := []byte(data)
	dt = append(dt, 0)
	var result = struct {
		signature []byte
	}{}
	result.signature = make([]byte, 64)

	code := casm.Call2Args(C.sign, provider, uintptr(unsafe.Pointer(&dt[0])), uintptr(unsafe.Pointer(&result)))

	
	if code != 0 {
		return []byte{}, &CProError{Code: code}
	}

	return result.signature, nil
}

func ReleaseProvider(provider uintptr) {
	casm.Call1ArgNoResult(C.release_provider, provider)
}
