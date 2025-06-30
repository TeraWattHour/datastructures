## Prefix Tree

Given a string `好的`, the generated structure looks like this:

```mermaid
graph TD;
    ROOT-- 好 -->好;
    好-- 的 -->好的;
    好的-->NULL
```

### Usage
```c
#include "prefix_tree.h'

int main() {
  Prefix_Node pn = {0};
  pn_insert(&pn, "hello, world!");
  pn_insert(&pn, "welcome");
  pn_insert(&pn, "hello everyone");
}
```
