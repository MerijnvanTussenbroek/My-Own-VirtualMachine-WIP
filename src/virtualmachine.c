#include "virtualmachine.h"
#include "stack_impl.h"

DEFINE_STACK(frame, Frame);
DEFINE_STACK(values, unsigned long int);