//trying recursion this way without recursion exactly
function factorial(n: nat): nat
{
    if n == 0 then 1 else n * factorial(n - 1)
}

method Factorial(n: nat) returns (result: nat)
    requires n > 0                              
    ensures result == factorial(n)                // correctness condition
{
    var i: nat := 1;
    result := 1;

    while i <= n
        invariant 1 <= i <= n + 1                 
        invariant result == factorial(i - 1)      // Partial correctness condition
        decreases n - i + 1                       // loop variant for total correctness
    {
        result := result * i;
        i := i + 1;
    }
}

method Main(){
    print factorial(5);
}