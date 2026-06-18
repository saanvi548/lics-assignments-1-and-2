method Abs(x: int) returns (x': int)
    requires true                          // No preconditions needed
    ensures x' >= 0                        // Absolute value is always non-negative
    ensures (x >= 0 ==> x' == x)           // If x is non-negative, result equals x
    ensures (x < 0 ==> x' == -x)           // If x is negative, result equals -x
{
    if x >= 0 {
        x' := x;
    } else {
        x' := -x;
    }
}






