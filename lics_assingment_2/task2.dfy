method FindFirstNegative(a: array<int>) returns (index: int)
  requires a.Length >= 0
  ensures -1 <= index < a.Length
  ensures index == -1 ==>
      (forall k :: 0 <= k < a.Length ==> a[k] >= 0)
  ensures index >= 0 ==>
      a[index] < 0 &&
      (forall k :: 0 <= k < index ==> a[k] >= 0)
{
  index := -1;
  var i := 0;
  
  while i < a.Length 
    invariant 0 <= i <= a.Length
    // This is the essential invariant for partial correctness:
    invariant (forall k :: 0 <= k < i ==> a[k] >= 0) 
    decreases a.Length - i
  {
    if a[i] < 0 {
      index := i;
      return;
    }
    i := i + 1;
  }
  index := -1;
}