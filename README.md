An Algorithm for getting the top X amount of elements of an array unsorted.
I had a very specific problem of needing the top X elements without them needing to be sorted.

N is number of total elements
X is number of elements I want from the array
R is the range of numbers

My previous method for doing this:
```c
for(int i = 0; i < X; i++)
{
  int highest = 0;
  int highestId = -1;
  for(int j = 0; j < N; j++)
  {
    if(array[j] > highest)
    {
      highestId = j;
      highest = array[j];
    }
  }

  if(highestId == -1)
    break;  //no more elements above 0

  //do stuff
  ...
}
```

PS: yes im not using Big O notation, uhh you get the idea probably

Is `N*X` which is quite slow, thinking about it considering I didn't need the output sorted there had to be a faster method.
Eventually I came up with an idea using half of counting sort.
Im counting per possible value all instances of that value, which is O(n)
```c
int valueCounter[R];
for(int i = 0; i < N; i++)
{
  if(array[i].value < 0 && array[i].value >= R)
    continue;

  valueCounter[array[i].value]++;
}
```

after that I'm going from the highest number to the lowest number and saving how many possible instances of that value are allowed in.
```c
int availableSpots = X;
for(int i = R; i >= 0; i--)
{
  if(availableSpots == 0)
  {
    valueCounter[i] = 0;
    continue;
  }

  if(availableSpots < valueCounter[i])
  {
    valueCounter[i] = availableSpots;
    availableSpots = 0;
    continue;
  }

  if(availableSpots >= valueCounter[i])
  {
    availableSpots -= valueCounter[i];
  }
}
```
We decrease the amount of available spots by the amount of instances of the value whenever go past an value thats used until the amount of instances of a value are less than the amount of available spots.
Then we set that value counter to the amount of spots still available, and anything after we set to 0.

Then we simply go through all elements in the array and check if there should be another instance of that elements value in the array
```c
int array2_index = 0;
for(int i = 0; i < N; i++)
{
  if(array[i].value < 0 && array[i].value >= R)
    continue;

  if(valueCounter[array[i].value] == 0)
    continue;
  
  valueCounter[array[i].value]--;

  array2[array2_index] = array[i];
  array2_index++;
}
```
In the end it ends up costing `N*2+R`, which scales quite a bit better depending on the circumstances

Compared to std::sort, which somebody offered as a solution prior, it ends up being quite a bit faster with the numbers I've tested

with N being 134 million
X being 65537 (16 bit integer limit)
and R being 10000
it only takes 500 milliseconds
std::sort ended up taking 57 seconds just to sort all the elements

Ofc this has a few caveats, mainly it requiring some kind of integer for counting sort part to work. So if you had floats you'd have to use some kind of limited precision most likely.
Also the range of elements needs to be somewhat low, tho for 134 million test it ended up not mattering if i had a range of possible values of 100 or 10000, 500ms either way

my original use case was with N 128, X 64, R 40.
Still ends up beating that, 18 microseconds vs 4 microseconds
