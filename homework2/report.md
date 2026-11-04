# 41443142

作業二

## 解題說明

### 第一題：實作 Polynomial 類別及其抽象資料型別 (ADT)

我透過將兩張圖的程式碼組合在一起，使的term與Polynomial類別搭起框架，然後再填入add,mult還有eval功能，並且我加入擴容部分，
使termArray不用擔心空間用完

功能add:
1. 建立一個新的多項式物件c用來儲存結果，建立兩指標用來表示a,b的多項式
2. while判斷未超過當前陣列長度，並透過exp來判斷指數相等就相加，指數不相等就移位到相同指數計算
3. for做結尾把剩下的部分放入c，最後return c

功能mult:
1. 建立一個新的多項式物件d用來儲存結果
2. for迴圈把每一個係數相乘指數相加
3. 新係數不等於0就填入暫存多項式中
4. 利用功能add把所有係數相加，最後return d

功能eval:
1. 建立一個total值來儲存算好的數
2. for迴圈帶入數字，並計算x的次方乘以係數
3. 算完的值加入total，最後return total

功能newterm:
1. 

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

以下為第一二題共用程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;
class Term
{
	friend class Polynomial;
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	private:
		float coef;
		int exp;
};
class Polynomial
{
	private:
		Term *termArray;
		int capacity;
		int terms;
	public:
		Polynomial() :capacity(2), terms(0)
		{
			termArray = new Term[capacity];
		}
		Polynomial Add(const Polynomial b)
		{
			Polynomial c;
			int aPos = 0, bPos = 0;
			while((aPos<terms)&&(bPos<b.terms))
			{
				if (termArray[aPos].exp == b.termArray[bPos].exp)
				{
					float t = termArray[aPos].coef + b.termArray[bPos].coef;
					if (t) c.newTerm(t,termArray[aPos].exp);
					aPos++;
					bPos++;
				}
				else if (termArray[aPos].exp < b.termArray[bPos].exp)
				{
					c.newTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
					bPos++;
				}
				else
				{
					c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
					aPos++;
				}
			}
			for (; aPos < terms; aPos++)
			{
				c.newTerm(termArray[aPos].coef,termArray[aPos].exp);
			}
			for (; bPos < b.terms; bPos++)
			{
				c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			}
			return c;
		}
		Polynomial Mult(Polynomial b)
		{
			Polynomial d;
			for (int i = 0; i < terms; i++)
			{
				Polynomial temp;
				for (int j = 0; j < b.terms; j++)
				{
					float ncoef= termArray[i].coef * b.termArray[j].coef;
					int nexp = termArray[i].exp + b.termArray[j].exp;
					if (ncoef != 0)
					{
						temp.newTerm(ncoef, nexp);
					}
				}
				d = d.Add(temp);
			}
			return d;
		}
		float Eval(float x)
		{
			float total = 0;
			for (int i = 0; i < terms; i++) {
				total += termArray[i].coef * pow(x, termArray[i].exp);
			}
			return total;
		}
		void newTerm(const float theCoef, const int theExp)
		{
			if (theCoef == 0)return;
			if (terms == capacity)
			{
				capacity *= 2;
				Term* temp = new Term[capacity];
				copy(termArray,termArray+terms,temp);
				delete []termArray;
				termArray = temp;
			}
			termArray[terms].coef = theCoef;
			termArray[terms++].exp = theExp;
		}
		friend ostream& operator<<(ostream& os, const Polynomial& p);
		friend istream& operator>>(istream& is, Polynomial& p);
};
ostream& operator<<(ostream& os, const Polynomial& p) {
	if (p.terms == 0) {
		os << "0";
		return os;
	}
	for (int i = 0; i < p.terms; i++) {
		if (i > 0 && p.termArray[i].coef > 0) os << "+";
		os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
	}
	return os;
}

istream& operator>>(istream& is, Polynomial& p) {
	int numTerms;
	cout << "輸入非零項的總個數: ";
	is >> numTerms;
	for (int i = 0; i < numTerms; i++) {
		float c;
		int e;
		cout << "輸入第 " << i + 1 << " 項的係數與指數: ";
		is >> c >> e;
		p.newTerm(c, e);
	}
	return is;
}
int main()
{
	Polynomial p1, p2, p3, p4,p5;
	int x, op;
	cout << "=== 開始輸入第一個多項式 ===" << endl;
	cin >> p1;
	cout << "=== 開始輸入第二個多項式 ===" << endl;
	cin >> p2;
	p3 = p1.Add(p2);
	p4 = p1.Mult(p2);
	cout << "選功能:";
	cin >> op;
	switch(op)
	{
		case 1:
			p3 = p1.Add(p2);
			cout << "相加=>" << p3 << endl;
			break;
		case 2:
			p4 = p1.Mult(p2);
			cout << "相乘=>" << p4 << endl;
			break;
		case 3:
			cin >> x;
			cout << "相加=" << p3.Eval(x) << endl;
			cout << "相乘=" << p4.Eval(x) << endl;
			break;
		default:
			break;

	}
	return 0;
}
```

## 效能分析

### 第一題

1. 時間複雜度:

	整體時間複雜度： $O(A(m, n))$

	詳細分析：每次執行遞迴呼叫或執行 B 的 while 迴圈次數，會與最終計算出來的結果數值 $A(m, n)$ 成正比。

	隨 $m$ 值的變化，時間複雜度呈階梯式暴增：

		 $m = 0$ ： $O(1)$ ，直接回傳 $n+1$ 。
		 $m = 1$ ： $O(n)$ ，結果為 $n+2$ 。
		 $m = 2$ ： $O(n)$ ，結果為 $2n+3$ 。
		 $m = 3$ ： $O(2^n)$ ，呈指數級（Exponential）成長。
		 $m = 4$ ： $O(2^{2^{\cdot^{\cdot^2}}})$（高度為 $n+3$ 的 2 的塔），呈超指數級（Hyper-exponential）成長。

2. 空間複雜度:

	整體空間複雜度： $O(A(m, n))$

	詳細分析：

	遞迴版 A(m, n)：

		佔用記憶體：系統呼叫堆疊（Call Stack）。
		空間大小：取決於最大遞迴深度。當 $m=3, n \ge 11$ 或 $m \ge 4$ 時，遞迴深度超過 Stack 限制，會發生 Stack Overflow。

	非遞迴版 B(m, n)：

		佔用記憶體：系統堆積區（Heap Memory，經由 new int[capacity] 配置）。
		空間大小：取決於自訂 Stack 中元素數量的最大值。雖然突破了 Call Stack 的大小限制，但在 $m \ge 4$ 時，Stack 佔用的 Heap 記憶體會暴增至數 GB 甚至數 TB，最終引發 Out of Memory（記憶體耗盡）。

### 第二題

1. 時間複雜度:
   整體時間複雜度： $O(n \cdot 2^n)$ (其中 $n$ 為字串長度 a.length())
   
   詳細分析：
   
   1. 遞迴樹節點數：

      		- 對於長度為 $n$ 的字串，每個字元都有「選」與「不選」兩種分支，形成的二元決策樹共有 $2^n$ 個葉子節點（即 $2^n$ 個子集合）。
   2. 單一節點開銷：

			- 在到達葉子節點（index == a.length()）時，印出長度為 $\vert{}current\vert{}$ 的字串需花費$O(\vert{}current\vert{})$ 的時間，平均開銷為 $O(n)$。
			- 在非葉子節點時，執行 current + a[index] 會建立新的 std::string 物件並複製內容，開銷同樣為 $O(n)$。
   3. 總時間複雜度為樹的總節點數乘以單次操作成本：$O(2^n) \times O(n) = O(n \cdot 2^n)$。

3. 空間複雜度:
   整體空間複雜度：$O(n^2)$(若不考慮隱式複製優化為 $O(n^2)$；若僅算最大遞迴深度為 $O(n)$)
   
   詳細分析：
   
   1. Call Stack 深度：遞迴樹的最大深度為 $n + 1$（從 index = 0 到 index = n），因此系統 Call Stack 空間為 $O(n)$。
   2. 記憶體複製開銷：

      		- 由於參數採值傳遞（Pass-by-value） string current，每次遞迴呼叫都會複製一份字串。
      		- 在最深的 Stack 層級中，同時存在於 Stack 上的字串長度總和約為 $1 + 2 + \dots + n = O(n^2)$。
   3. 與回溯法 (Backtracking) 對比：若改用 引用傳遞（Pass-by-reference）string& current + push_back/pop_back，空間複雜度可最佳化至 $O(n)$。

## 測試與驗證

### 測試案例

#### 第一題

| M | N | 理論計算公式 / 過程         | 理論正確值  | 測試重點                       |
|---|---|---------------------------|------------|--------------------------------|
| 0 | 0 | $0 + 1$                   | 1          | 基本終止條件 (Base Case)        |
| 0 | 5 | $5 + 1$                   | 6          | $m=0$ 的一般情況                |
| 1 | 0 | $A(0, 1) = 1 + 1$         | 2          | $n=0$ 觸發 $A(m-1, 1)$ 的邊界   |
| 1 | 3 | $n + 2 = 3 + 2$           | 5          | 線性成長階段                    |
| 2 | 2 | $2 \times 2 + 3$          | 7          | 線性成長階段                    |
| 3 | 1 | $2^{(1+3)} - 3 = 16 - 3$  | 13         | 指數成長開端                    |
| 3 | 4 | $2^{(4+3)} - 3 = 128 - 3$ | 125        | 數字開始膨脹、Stack 開始動態擴容 |

#### 第二題

| 測試字串 a | 長度 n | 理論子集合數 ($2^n$) | 預期輸出結果                                   | 測試重點           |
|-----------|--------|---------------------|-----------------------------------------------|-------------------|
| a         | 1      | $2^1 = 2$           | () (a)                                        | 單一字元邊界測試   |
| ab        | 2      | $2^2 = 4$           | () (b) (a) (a, b)                             | 一般基本組合       |
| abc       | 3      | $2^3 = 8$           | () (c) (b) (b, c) (a) (a, c) (a, b) (a, b, c) | 標準三元素組合測試  |

### 編譯與執行指令

#### 第一題

```shell
g++ -O2 資料結構h1-1.cpp -o 資料結構h1-1.exe
.\資料結構h1-1.exe
3 4
125
125
```

#### 第二題

```shell
g++ -std=c++11 -O2 "資料結構h1-2.cpp" -o 資料結構h1-2.exe
.\資料結構h1-2.exe
a b c
()
(c)
(b)
(b,c)
(a)
(a,c)
(a,b)
(a,b,c)
```

## 申論及開發報告

第一題主要來說就是就是寫遞迴與非遞迴的兩種辦法,透過題目給的公式可以解決遞迴的方法,非遞迴的方式則是由堆疊來執行,因為規定限制沒法直接使用堆疊,所以只能自製堆疊,當然還得記得堆疊先進後出的順序

第二題主要是使用遞迴運算,一個一個慢慢搜出來的,先從都不選開始,第一步先選最後一個,類似樹狀結構,分枝是選與不選,然後一直選到到全部都選在結束印出


