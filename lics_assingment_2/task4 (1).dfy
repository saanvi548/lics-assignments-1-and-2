// wrote for verification
function T(n: nat): nat
{ 
    if n == 0 then 0
    else if n == 1 then 1
    else if n == 2 then 1
    else T(n-1) + T(n-2) + T(n-3)
}

method Tribonacci(n: nat) returns (result: nat)
    requires n >= 0
    ensures result == T(n)
{
    if n == 0 {
        result := 0;
        return;
    }

    if n == 1 || n == 2 {
        result := 1;
        return;
    }

    var a: nat := 0; 
    var b: nat := 1; 
    var c: nat := 1; 
    var i: nat := 3;
    result := c;

    while i <= n
        invariant 3 <= i <= n + 1
        invariant a == T(i - 3)
        invariant b == T(i - 2)
        invariant c == T(i - 1)
        invariant result == c
        decreases n - i + 1
    {
        result := a + b + c;
        // update rolling variables
        a := b;
        b := c;
        c := result;
        i := i + 1;
    }

    // at loop exit: i = n + 1 → result == T(n)
}

method Main(){
    print T(3) ;

}
