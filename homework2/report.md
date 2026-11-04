# 41443142

作業二

## 解題說明

### 第一題：實作 Polynomial 類別及其抽象資料型別 (ADT)

我透過將兩張圖的程式碼組合在一起，使的 term 與 Polynomial 類別搭起框架，然後再填入 add , mult 還有 eval 功能，並且我加入擴容部分，
使 termArray 不用擔心空間用完

#### 功能add:
1. 建立一個新的多項式物件 c 用來儲存結果，建立兩指標用來表示 a , b 的多項式
2. while 判斷未超過當前陣列長度，並透過 exp 來判斷指數相等就相加，指數不相等就移位到相同指數計算
3. for 做結尾把剩下的部分放入 c，最後 return c

#### 功能mult:
1. 建立一個新的多項式物件 d 用來儲存結果
2. for 迴圈把每一個係數相乘指數相加
3. 新係數不等於 0 就填入暫存多項式中
4. 利用功能 add 把所有係數相加，最後 return d

#### 功能eval:
1. 建立一個 total 值來儲存算好的數
2. for 迴圈帶入數字，並計算 x 的次方乘以係數
3. 算完的值加入 total ，最後 return total

#### 功能newterm:
1. 如果係數等於 0 ，回傳空值
2. 如果空間滿了，就把空間翻倍，建立新空間複製資料丟回去，丟回去前順便刪掉舊空間
3. 將新資料存入空間

### 第二題:編寫 C++ 函數來輸入和輸出多項式並且重載 << 和 >> 運算子

#### ostream& operator<< (用來輸出)
1. 如果多項式中沒有任何非零項，直接印出 0 並結束
2. 如果這不是第一項，該項係數為正數，補上 + 號
3. 輸出標準格式(ex:3x^2+...)

#### istream& operator>> (用來輸入)
1. 先向使用者詢問共有幾項
2. 將輸入的係數與指數作為新項加入到物件 p 的動態陣列 termArray

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

#### 1. newTerm(theCoef, theExp) 函式
1. 時間複雜度：
	- 正常情況(不用空間翻倍): $O(1)$
	- 觸發空間翻倍: $O(k)$ (k 為當前項數)
2. 空間複雜度： $O(1)$ (擴容需要 $O(capacity)$ )
#### 2. Add(b) 函式
1. 時間複雜度： $O(m+n)$
採用雙指標法走訪 A（m 項）與 B（n 項）	
2. 空間複雜度： $O(1)$ (擴容需要 $O(capacity)$ )

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


