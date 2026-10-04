# 41443142

作業一

## 解題說明

### 第一題：Ackermann 函數

需要用遞迴與非遞迴兩種方式來解決問題
輸入整數m和n

函式A:遞迴版Ackermann
輸入條件三個:

1. m==0時,回傳n+1
2. n==0時,回傳函式A,並設m=m-1,n=1
3. 其他狀況時,回傳函式A,並設m=m-1,n=A(m,n-1)

經過計算後,回傳函式A值

函式B:非遞迴版Ackermann

1. 使用動態記憶體配置,設定top=-1
2. 用push_stack推入初始m
3. 如果top>=0,推出top數值判斷與計算
4. 如果m==0,n+1
5. 否則判斷n==0,n=1
6. 其他則判斷推入數值m-1,再推入數值m,最後n-1
7. 清空堆疊函式最後回傳數值n

使用自製堆疊函式push_stack和pop_stack達成
- push_stack使用動態擴容避免動態記憶體空間用完,同時可以將數值推入堆疊的top
- pop_stack推出數值並回傳給函式B

### 第二題:冪集合

輸入字串a,並交由powerset函式來計算與印出

設定函式Powerset:

1. 設定初始選定值index==0,選定組合為""
2. 再來開啟第一步,執行選與不選的遞迴
3. 執行遞迴同時,將選完的組合存入字串current
4. 如果選取值index==a的長度,印出( ,進入迴圈執行印出選定組合,在印出)
5. 最後迴傳答案

		- 例如:輸入字串a,b,c
   			不選a不選b不選c,答案印出()
   			不選a不選b選c,答案印出(c)
   			不選a選b不選c,答案印出(b)
   			不選a選b選c,答案印出(b,c)
   			選a不選b不選c,答案印出(a)
   			以此類推直到印出所有答案

## 程式實作

以下為第一題程式碼：

```cpp
#include<iostream>
#include<cmath>

using namespace std;

void push_stack(int*& s, int& top, int& capacity, int val)
{
	top++;
	if (top >= capacity)
	{
		int new_capacity = capacity * 2;
		int* new_s = new int[new_capacity];
		for (int i = 0; i < capacity; i++)
		{
			new_s[i] = s[i];
		}
		delete[] s;
		s = new_s;
		capacity = new_capacity;
	}
	s[top] = val;
}

int pop_stack(int*& s, int& top)
{
	int val = s[top];
	top--;
	return val;
}

// 遞迴版本
int A(int m, int n)
{
	if (m == 0)
	{
		return n + 1;
	}
	else if (n == 0)
	{
		return A(m - 1, 1);
	}
	else
	{
		return A(m - 1, A(m, n - 1));
	}
}

// 非遞迴版本 (自訂 Stack)
int B(int m, int n)
{
	int capacity = 16;
	int top = -1;
	int* s = new int[capacity];
	push_stack(s, top, capacity, m);
	while (top >= 0)
	{
		m = pop_stack(s, top);
		if (m == 0)
		{
			n++;
		}
		else if (n == 0)
		{
			push_stack(s, top, capacity, m - 1);
			n = 1;
		}
		else
		{
			push_stack(s, top, capacity, m - 1);
			push_stack(s, top, capacity, m);
			n--;
		}
	}
	delete[] s;
	return n;
}

int main()
{
	int m, n, a, b;
	while (cin >> m >> n)
	{
		a = A(m, n);
		cout << a << endl;

		b = B(m, n);
		cout << b << endl;
	}
	return 0;
}
```

以下為第二題程式碼：

```cpp
#include <iostream>
#include <string>

using namespace std;


void Powerset(const string& a, int index, string current)
{
	if (index == a.length())
	{
		cout << "(";
		for (size_t i = 0; i < current.length(); i++)
		{
			cout << current[i];
			if (i + 1 < current.length())
			{
				cout << ", ";
			}
		}
		cout << ")" << endl;
		return;
	}

	Powerset(a, index + 1, current);

	Powerset(a, index + 1, current + a[index]);
}

int main()
{
	string a;
	while (cin >> a)
	{
		Powerset(a, 0, "");
	}
	return 0;
}
```

## 效能分析

### 第一題

1. 時間複雜度:

	整體時間複雜度：$O(A(m, n))$

	詳細分析：每次執行遞迴呼叫或執行 B 的 while 迴圈次數，會與最終計算出來的結果數值 $A(m, n)$ 成正比。

	隨 $m$ 值的變化，時間複雜度呈階梯式暴增：

		$m = 0$：$O(1)$，直接回傳 $n+1$。
		$m = 1$：$O(n)$，結果為 $n+2$。
		$m = 2$：$O(n)$，結果為 $2n+3$。
		$m = 3$：$O(2^n)$，呈指數級（Exponential）成長。
		$m = 4$：$O(2^{2^{\cdot^{\cdot^2}}})$（高度為 $n+3$ 的 2 的塔），呈超指數級（Hyper-exponential）成長。

2. 空間複雜度:

	整體空間複雜度：$O(A(m, n))$

	詳細分析：

	遞迴版 A(m, n)：

		佔用記憶體：系統呼叫堆疊（Call Stack）。
		空間大小：取決於最大遞迴深度。當 $m=3, n \ge 11$ 或 $m \ge 4$ 時，遞迴深度超過 Stack 限制，會發生 Stack Overflow。

	非遞迴版 B(m, n)：

		佔用記憶體：系統堆積區（Heap Memory，經由 new int[capacity] 配置）。
		空間大小：取決於自訂 Stack 中元素數量的最大值。雖然突破了 Call Stack 的大小限制，但在 $m \ge 4$ 時，Stack 佔用的 Heap 記憶體會暴增至數 GB 甚至數 TB，最終引發 Out of Memory（記憶體耗盡）。

### 第二題

## 測試與驗證

### 測試案例

| M | N | 理論計算公式 / 過程         | 理論正確值  | 測試重點                       |
|---|---|---------------------------|------------|--------------------------------|
| 0 | 0 | $0 + 1$ | 0               | 1          | 基本終止條件 (Base Case)        |
| 0 | 5 | $5 + 1$ | 1               | 6          | $m=0$ 的一般情況                |
| 1 | 0 | $A(0, 1) = 1 + 1$         | 2          | $n=0$ 觸發 $A(m-1, 1)$ 的邊界   |
| 1 | 3 | $n + 2 = 3 + 2$           | 5          | 線性成長階段                    |
| 2 | 2 | $2 \times 2 + 3$          | 7          | 線性成長階段                    |
| 3 | 1 | $2^{(1+3)} - 3 = 16 - 3$  | 13         | 指數成長開端                    |
| 3 | 4 | $2^{(4+3)} - 3 = 128 - 3$ | 125        | 數字開始膨脹、Stack 開始動態擴容 |

### 編譯與執行指令

```shell
g++ -O2 資料結構h1-1.cpp -o 資料結構h1-1.exe
.\資料結構h1-1.exe
3 4
125
125
```

### 結論

## 申論及開發報告

第一題主要來說就是就是寫遞迴與非遞迴的兩種辦法,透過題目給的公式可以解決遞迴的方法,非遞迴的方式則是由堆疊來執行,因為規定限制沒法直接使用堆疊,所以只能自製堆疊,當然還得記得堆疊先進後出的順序
