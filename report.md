# 41443142

作業一

## 解題說明

### 第一題：Ackermann 函數

需要用遞迴與非遞迴兩種方式來解決問題
輸入整數m和n

函式A:遞迴版Ackermann
輸入條件三個:

1.m==0時,回傳n+1
2.n==0時,回傳函式A,並設m=m-1,n=1
3.其他狀況時,回傳函式A,並設m=m-1,n=A(m,n-1)

經過計算後,回傳函式A值

函式B:非遞迴版Ackermann

使用自製堆疊函式push_stack和pop_stack達成
push_stack使用動態擴容避免動態記憶體空間用完,同時可以將數值推入堆疊的top
pop_stack推出數值並回傳給函式B

使用動態記憶體配置,設定top=-1
用push_stack推入初始m
如果top>=0,推出top數值判斷與計算
如果m==0,n+1
否則判斷n==0,n=1
其他則判斷推入數值m-1,再推入數值m,最後n-1
清空堆疊函式最後回傳數值n

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

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(\log n)$。
2. 空間複雜度：空間複雜度為 $O(100\times \log n + \pi)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
