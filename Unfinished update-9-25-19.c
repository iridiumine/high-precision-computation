#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType char
#define MAXSIZE 400

int flag = 0;

typedef struct LNode *List;
struct LNode {
    ElementType Data;
    List Next;
};

List PtrL, X, Y, X1, X2;

List MakeEmpty() {
    List PtrL;
    
    PtrL = (List)malloc(sizeof(struct LNode));
    
    return PtrL;
}

int Length(List PtrL) {
    List p = PtrL;
    
    int length = 0;
    
    while (p) {
        p = p->Next;
        length++;
    }
    
    return length;
}

int Distance_point(List PtrL) {
    int distance = 0;
    List p = PtrL;
    
    while (p != NULL && p->Data != '.') {
        p = p->Next;
        distance++;
    }
    
    return distance;
}

List Find_point(List PtrL) {
    List p = PtrL;
    
    while (p != NULL && p->Data != '.') {
        p = p->Next;
    }
    
    return p;
}

List Find_Kth(int K, List PtrL) {
    List p = PtrL;
    
    int i = 1;
    
    while (p != NULL && i < K) {
        p = p->Next;
        i++;
    }
    
    if (i == K) {
        return p;
    }
    else {
        return NULL;
    }
}

int Find_Kth_number(int K, List PtrL) {
    List p = PtrL;
    
    int i = 1;
    
    while (p != NULL && i < K) {
        p = p->Next;
        i++;
    }
    
    if (i == K) {
        return p->Data - '0';
    }
    else {
        return -1;
    }
}

void Insert_zero_before(List PtrL) {
    List p = (List)malloc(sizeof(struct LNode));
    
    p->Data = '0';
    p->Next = PtrL->Next;
    PtrL->Next = p;
}

void Insert_zero_after(List PtrL) {
    List p = (List)malloc(sizeof(struct LNode));
    
    p->Data = '0';
    p->Next = NULL;
    PtrL->Next = p;
}

void Change(int item, int K, List PtrL) {
    List p = Find_Kth(K, PtrL);
    
    p->Data = item + '0';
}

List Insert(ElementType x, List PtrL) {
    List p = (List)malloc(sizeof(struct LNode));
    
    p->Data = x;
    p->Next = NULL;
    PtrL->Next = p;
    
    return PtrL;
}

void Move(List PtrL) {
    int d1 = Distance_point(PtrL);
    
    while (d1 < 200) {
        Insert_zero_before(PtrL);
        d1++;
    }
    
    int d2 = Length(PtrL);
    
    for (; d2 < 400; d2++) {
        List p = Find_Kth(d2, PtrL);
        Insert_zero_after(p);
    }
}

List Write_without_Move(List PtrL) {
    char c;
    List p = PtrL;
    
    while ((c = getchar()) != '\n') {
        Insert(c, p);
        int i = Length(PtrL);
        p = Find_Kth(i, PtrL);
    }
    
    return PtrL;
}

List Write_with_Move(List PtrL) {
    char c;
    List p = PtrL;
    
    while ((c = getchar()) != '\n') {
        Insert(c, p);
        int i = Length(PtrL);
        p = Find_Kth(i, PtrL);
    }
    
    Move(PtrL);
    
    return PtrL;
}

List Multiply(List X1, List X2) {
    char temp1[MAXSIZE];
    char temp2[MAXSIZE];
    
    List p = NULL;
    
    memset(temp1, 0, sizeof(temp1));
    memset(temp2, 0, sizeof(temp2));
    
    int i1 = Length(X1), j1 = 2;
    int i2 = Length(X2), j2 = 2;
    
    for (; i1 > 0; i1--) {
        if (Find_Kth_number(i1, X1) != -2) {
            temp1[MAXSIZE - j1] = Find_Kth_number(i1, X1) + '0';
            j1++;
        }
    }
    
    for (; i2 > 0; i2--) {
        if (Find_Kth_number(i2, X2) != -2) {
            temp2[MAXSIZE - j2] = Find_Kth_number(i2, X1) + '0';
            j2++;
        }
    }
    
    return p;
}

void Print_without_Move(List PtrL) {
    List p = PtrL;
    
    while (p) {
        printf("%c", p->Data);
        p = p->Next;
    }
}

void Print_with_Move(List PtrL) {
    int i, j;
    int flag1 = -1, flag2 = -1;
    
    for (i = 2; i < 201; i++) {
        List p = Find_Kth(i, PtrL);
        if (p->Data != '0') {
            flag1 = 0;
        }
        if (flag1 == 0 || (flag1 == -1 && i == 200)) {
            printf("%c", p->Data);
        }
        p = p->Next;
    }
    
    for (j = 399; j > 202; j--) {
        List p = Find_Kth(j, PtrL);
        if (p->Data != '0') {
            flag2 = 0;
            break;
        }
    }
    
    for (i = 201; i <= j; i++) {
        List p = Find_Kth(i, PtrL);
        printf("%c", p->Data);
    }
    
    printf("\n");
}

List Add(List X1, List X2) {
    List p = MakeEmpty();
    List q = (List)malloc(sizeof(struct LNode));
    
    int i;
    
    p->Next = q;
    q->Data = '.';
    q->Next = NULL;
    
    Move(p);
    
    for (i = 200; i >= 1; i--) {
        if (i == 200) {
            int a1 = Find_Kth_number(202, X1);
            int b1 = Find_Kth_number(202, X2);
            int sum1 = a1 + b1;
            if (sum1 >= 10) {
                flag = 1;
            }
        }
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int sum = a + b + flag;
        flag = 0;
        if (sum >= 10) {
            flag = 1;
            sum = sum - 10;
        }
        Change(sum, i, p);
    }
    
    for (i = 399; i >= 202; i--) {
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int sum = a + b + flag;
        flag = 0;
        if (sum >= 10) {
            flag = 1;
            sum = sum - 10;
        }
        Change(sum, i, p);
    }
    
    return p;
}

List Subtract(List X1, List X2) {
    List p = MakeEmpty();
    List q = (List)malloc(sizeof(struct LNode));
    
    int i;
    
    p->Next = q;
    q->Data = '.';
    q->Next = NULL;
    
    Move(p);
    
    for (i = 399; i >= 202; i--) {
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int subtraction = a - b + flag;
        flag = 0;
        if (subtraction < 0) {
            subtraction = subtraction + 10;
            flag = -1;
        }
        Change(subtraction, i, p);
    }
    
    for (i = 200; i >= 1; i--) {
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int subtraction = a - b + flag;
        flag = 0;
        if (subtraction < 0) {
            subtraction = subtraction + 10;
            flag = -1;
        }
        Change(subtraction, i, p);
    }
    
    if (flag == -1) {
        printf("-");
        flag = 0;
        return Subtract(X2, X1);
    }
    
    return p;
}

int main(int argc, char const *argv[]) {
    
    return 0;
}
