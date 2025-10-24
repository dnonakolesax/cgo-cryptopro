package casm

// https://github.com/golang/go/blob/bbf8f423abc9f92f4c1c5d98281ed0b21107b00d/src/runtime/runtime2.go#L298
type gobuf struct { //nolint:unused // used in asm
	sp, pc, g, ctxt, ret, lr, bp uintptr
}

// https://github.com/golang/go/blob/bbf8f423abc9f92f4c1c5d98281ed0b21107b00d/src/runtime/runtime2.go#L385
type stack struct { //nolint:unused // used in asm
	lo, hi uintptr
}

// https://github.com/golang/go/blob/bbf8f423abc9f92f4c1c5d98281ed0b21107b00d/src/runtime/runtime2.go#L396
type g struct { //nolint:unused // used in asm
	stack                    stack
	stackguard0, stackguard1 uintptr

	_panic, _defer uintptr
	m              *m
	sched          gobuf
}

// https://github.com/golang/go/blob/bbf8f423abc9f92f4c1c5d98281ed0b21107b00d/src/runtime/runtime2.go#L528
type m struct { //nolint:unused // used in asm
	g0 *g
}
