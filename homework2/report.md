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
> 採用雙指標法走訪 A（m 項）與 B（n 項），迴圈每次比較指數後，至少會讓 aPos 或 bPos 前進 1 步，總比較與複製次數最多為 m + n 次	
2. 空間複雜度： $O(m+n)$
> 建立回傳的 Polynomial c，最壞情況下（兩多項式完全沒有相同的指數項），c 的 termArray 需要儲存 m + n 個項

#### 3. Mult(b) 函式
1. 時間複雜度： $O(m^2 \cdot n)$
	- 外層迴圈走訪 $A$ 的 $m$ 個項，內層走訪 $B$ 的 $n$ 個項，單項相乘計算共執行 m x n次
	- 每次外層迴圈算出包含 $n$ 項的 temp 後，會呼叫一次 d = d.Add(temp)
	- 隨迴圈推進，d 的項數會從 n 逐步累積到 m x n 在第 i 次疊加時，Add 的時間開銷為 $\mathcal{O}(i \cdot n + n)$
	- 總時間為 $\sum_{i=1}^{m} \mathcal{O}(i \cdot n) = \mathcal{O}(m^2 \cdot n)$
2. 空間複雜度： $O(m \cdot n)$
> 最終相乘結果 d 在最壞情況下（所有項指數組合皆不同）最多會產生 m x n 項

#### 4. Eval(x) 函式
1. 時間複雜度： $O(k)$（k 為該多項式的項數）
> 迴圈執行 k 次，每次進行一次 pow(x, exp) 與乘加運算
2. 空間複雜度： $O(1)$
> 僅使用單一浮點數變數 total 累加結果

### 第二題

#### 1. 輸出運算子：operator<<
1. 時間複雜度： $O(N)$
	- 迴圈會固定走訪 p.terms 次（共 N 項
	- 每次迴圈執行一次判斷與標準輸出串流（os << ...）寫入，單次操作耗時 $O(1)$
 	- 總時間與多項式的項數 N 成正比
2. 空間複雜度： $O(1)$
	- 函式僅採用 const Polynomial& p 引用傳遞，不會建立多項式的副本
	- 僅使用區域變數 i 進行計數，沒有額外配置動態記憶體或容器

#### 2. 輸入運算子：operator>>
1. 時間複雜度：$O(N)$
	- 迴圈會根據使用者輸入的 numTerms（N 項）執行 N 次
	- 每次迴圈內部呼叫 p.newTerm(c, e)：
		> 正常情況下，插入項目為 $O(1)$
  		> 即使過程中觸發動態擴容，根據均攤分析，連續插入 N 項的總擴容複製成本為 $O(N)$
	- 平均分攤到每一步依然是線性時間 $O(N)$
2. 空間複雜度：$O(N)$
	- 輸入過程中，newTerm 會根據輸入的項數 N 動態配置記憶體（new Term \[capacity]\ ）
 	- 最終 termArray 的大小會成長到能容納 N 個項（容量約為 $O(N)$）
  	- 區域變數（i, c, e, numTerms）僅佔用 $O(1)$ 的常數空間

## 測試與驗證

### 測試案例

#### 第一二題共用

| 第一個多項式輸入 (P1) | 第二個多項式輸入 (P2)     | 功能 (op) | 程式實際輸出結果      | 驗證重點                                        |
|----------------------|-------------------------|-----------|---------------------|-------------------------------------------------|
| 2<br>3 2<br>2 1      | 3<br>4 2<br>-1 1<br>5 0 | 1 (相加)  | 相加=>7x^2+1x^1+5x^0 | 一般多項式對應次方合併                           |
| 2<br>5 3<br>2 1      | 3<br>-5 3<br>4 2<br>-2 1| 1 (相加)  | 相加=>4x^2           | $5x^3$ 與 $-5x^3$ 完全抵銷（if (t) 過濾 0 係數） |
| 2<br>2 1<br>3 0      | 0 (零多項式)             | 2 (相乘)  | 相乘=>0              | 乘數為 0 時的邊界條件處理                        |

### 編譯與執行指令

#### 第一二題共用

```shell
g++ -O2 資料結構h2-1.cpp -o 資料結構h2-1.exe
.\資料結構h2-1.exe
2
5 3
2 1
3
-5 3
4 2
-2 1
1
相加=>4x^2
```

## 申論及開發報告

第一題主要是將提供程式補全並完善功能，在於一些邏輯上的問題，總讓人頭疼，我認為這是應該盡力培養好的專業素養

第二題則是對於第一題的程式補全了更多功能，這種輸入輸出的方法，我也是第一次完成，所以一開始我是沒有什麼頭緒的，後來深碗有提到類似議題，我才了解到還能這麼做
