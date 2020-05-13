# 2020년 5월 3주차 알고리즘

## 목표

1. TreePrinter 구현
    - 콘솔창에서 트리구조를 렌더링
2. RedBlackTree 알고리즘 구현
    - `insert()` 메서드만 구현 (삭제연산은 삽입연산과 동일한 메커니즘을 가지기 때문)
3. 다음의 테스트 결과가 나오는지 확인

```javascript
const tree = new RedBlackTree(); 

// 프린트는 왼쪽노드가 먼저 위에 오는 순서로 되어있음
tree.insert(10);
tree.insert(20);
// 10
//  `- 20
printTree(tree);
tree.insert(30);
// 20
//  |- 10
//  `- 30
printTree(tree);
tree.insert(40);
tree.insert(50);
// 20
//  |- 10
//  `- 40
//      |- 30
//      `- 50
printTree(tree);
tree.insert(18);
// 20
//  |- 15
//  |   |- 10
//  |   `- 18
//  `- 40
//      |- 30
//      `- 50
printTree(tree)
tree.insert(25);
tree.insert(38);
tree.insert(28);
// 30
//  |- 20
//  |   |- 15
//  |   |   |- 10
//  |   |   `- 18
//  |   `- 25
//  |       `- 28
//  `- 40
//      |- 38
//      `- 50
printTree(tree);
```

## 레퍼런스

- [https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)
