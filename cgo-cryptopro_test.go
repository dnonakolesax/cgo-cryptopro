package ccp

import (
	"fmt"
	"testing"
)

func TestCoreLogic(t *testing.T) {
	container := "\\\\.\\HDIMAGE\\de47006e0-87a9-36a2-dfd7-5c65af93896"
	password := "notsosampletext2003"
	cont, err := AcquireContext(container, password)
	if err != nil {
		t.Error(err.Error())
	}

	sign, err := SignData(cont, "testmessage")
	if err != nil {
		t.Error(err.Error())
	}

	for i := 0; i < len(sign); i++ {
		fmt.Printf("%02x", sign[i])
	}

	fmt.Printf("\n")
	ReleaseProvider(cont)
}