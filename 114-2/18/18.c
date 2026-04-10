#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000 // 整數與小數最大各 60 位，相乘最大長度不過 240，1000 是非常安全的 Buffer

// 解析輸入字串：分離出正負號、小數位數，並將數字「反轉」存入陣列中（方便從最低位開始計算）
void parse(char *str, int *sign, char *digits, int *len, int *dec_len) {
    *sign = 1;
    if (str[0] == '-') {
        *sign = -1;
        str++;
    }
    int l = strlen(str);
    int dot_pos = -1;
    for (int i = 0; i < l; i++) {
        if (str[i] == '.') {
            dot_pos = i;
            break;
        }
    }
    
    int ptr = 0;
    char temp[MAX_LEN];
    if (dot_pos == -1) {
        *dec_len = 0; // 若沒有小數點
        for(int i = 0; i < l; i++) temp[ptr++] = str[i];
    } else {
        *dec_len = l - 1 - dot_pos; // 計算小數位數
        for(int i = 0; i < l; i++) {
            if (str[i] != '.') {
                temp[ptr++] = str[i];
            }
        }
    }
    *len = ptr;
    for (int i = 0; i < ptr; i++) {
        digits[i] = temp[ptr - 1 - i] - '0'; // 反轉並轉為數值 (0-9)
    }
    // 將未使用的陣列清零
    for (int i = ptr; i < MAX_LEN; i++) {
        digits[i] = 0;
    }
}

// 將兩數的小數點對齊（藉由補 0）
void align(char *d1, int *l1, int *dec1, char *d2, int *l2, int *dec2) {
    if (*dec1 < *dec2) {
        int diff = *dec2 - *dec1;
        for (int i = *l1 - 1; i >= 0; i--) d1[i + diff] = d1[i];
        for (int i = 0; i < diff; i++) d1[i] = 0;
        *l1 += diff;
        *dec1 = *dec2;
    } else if (*dec2 < *dec1) {
        int diff = *dec1 - *dec2;
        for (int i = *l2 - 1; i >= 0; i--) d2[i + diff] = d2[i];
        for (int i = 0; i < diff; i++) d2[i] = 0;
        *l2 += diff;
        *dec2 = *dec1;
    }
}

// 比較兩個已對齊的數字絕對值大小
int cmp(char *d1, int l1, char *d2, int l2, int dec) {
    int real_l1 = l1;
    while(real_l1 > dec + 1 && d1[real_l1 - 1] == 0) real_l1--;
    int real_l2 = l2;
    while(real_l2 > dec + 1 && d2[real_l2 - 1] == 0) real_l2--;
    
    if (real_l1 > real_l2) return 1;
    if (real_l1 < real_l2) return -1;
    for (int i = real_l1 - 1; i >= 0; i--) {
        if (d1[i] > d2[i]) return 1;
        if (d1[i] < d2[i]) return -1;
    }
    return 0;
}

// 純絕對值加法
void add(char *d1, int l1, char *d2, int l2, char *rd, int *rl) {
    int max_l = (l1 > l2) ? l1 : l2;
    int carry = 0;
    for (int i = 0; i < max_l; i++) {
        int v1 = (i < l1) ? d1[i] : 0;
        int v2 = (i < l2) ? d2[i] : 0;
        int sum = v1 + v2 + carry;
        rd[i] = sum % 10;
        carry = sum / 10;
    }
    *rl = max_l;
    if (carry > 0) {
        rd[*rl] = carry;
        (*rl)++;
    }
}

// 純絕對值減法 (假設 d1 >= d2)
void sub(char *d1, int l1, char *d2, int l2, char *rd, int *rl) {
    int borrow = 0;
    for (int i = 0; i < l1; i++) {
        int v1 = d1[i];
        int v2 = (i < l2) ? d2[i] : 0;
        int diff = v1 - v2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        rd[i] = diff;
    }
    *rl = l1;
}

// 格式化輸出，處理多餘的 0 與小數點
void print_bf(int sign, char *d, int l, int dec) {
    int is_zero = 1;
    for (int i = 0; i < l; i++) {
        if (d[i] != 0) { is_zero = 0; break; }
    }
    // 若結果為 0，直接輸出 0
    if (is_zero) {
        printf("0\n");
        return;
    }
    
    int shift = 0;
    // 移除小數部分的後導零
    while (shift < dec && d[shift] == 0) {
        shift++;
    }
    if (shift > 0) {
        for (int i = 0; i < l - shift; i++) {
            d[i] = d[i + shift];
        }
        l -= shift;
        dec -= shift;
    }
    
    // 移除整數部分的前導零 (保留至少 1 位數給個位數)
    while (l > dec + 1 && d[l - 1] == 0) {
        l--;
    }
    
    // 輸出負號
    if (sign == -1) printf("-");
    
    // 處理純小數的情況 (如 .123 -> 0.123)
    if (l <= dec) {
        printf("0.");
        for (int i = 0; i < dec - l; i++) printf("0");
        for (int i = l - 1; i >= 0; i--) printf("%d", d[i]);
    } else {
        // 一般輸出
        for (int i = l - 1; i >= 0; i--) {
            printf("%d", d[i]);
            if (i == dec && dec > 0) printf("."); // 遇到適當位置補上小數點
        }
    }
    printf("\n");
}

int main() {
    char s1[MAX_LEN], s2[MAX_LEN];
    if (scanf("%s %s", s1, s2) != 2) return 0;
    
    int sign1, sign2;
    char d1[MAX_LEN] = {0}, d2[MAX_LEN] = {0};
    int l1, l2, dec1, dec2;
    
    // 解析兩個字串
    parse(s1, &sign1, d1, &l1, &dec1);
    parse(s2, &sign2, d2, &l2, &dec2);
    
    // 為加法和減法創建一份備份 (因為 Align 會改動陣列與位數長度)
    char c_d1[MAX_LEN], c_d2[MAX_LEN];
    int c_l1 = l1, c_l2 = l2, c_dec1 = dec1, c_dec2 = dec2;
    memcpy(c_d1, d1, MAX_LEN);
    memcpy(c_d2, d2, MAX_LEN);
    
    // 對齊小數點
    align(c_d1, &c_l1, &c_dec1, c_d2, &c_l2, &c_dec2);
    int dec = c_dec1; // 對齊後兩者 dec 相等
    
    // === 加法區塊 ===
    char r_add[MAX_LEN] = {0}; int rl_add = 0, rs_add = 1;
    if (sign1 == sign2) {
        add(c_d1, c_l1, c_d2, c_l2, r_add, &rl_add);
        rs_add = sign1;
    } else {
        int c = cmp(c_d1, c_l1, c_d2, c_l2, dec);
        if (c >= 0) {
            sub(c_d1, c_l1, c_d2, c_l2, r_add, &rl_add);
            rs_add = sign1;
        } else {
            sub(c_d2, c_l2, c_d1, c_l1, r_add, &rl_add);
            rs_add = sign2;
        }
    }
    
    // === 減法區塊 === 
    // A - B 相當於 A + (-B)
    char r_sub[MAX_LEN] = {0}; int rl_sub = 0, rs_sub = 1;
    int sign2_sub = -sign2;
    if (sign1 == sign2_sub) {
        add(c_d1, c_l1, c_d2, c_l2, r_sub, &rl_sub);
        rs_sub = sign1;
    } else {
        int c = cmp(c_d1, c_l1, c_d2, c_l2, dec);
        if (c >= 0) {
            sub(c_d1, c_l1, c_d2, c_l2, r_sub, &rl_sub);
            rs_sub = sign1;
        } else {
            sub(c_d2, c_l2, c_d1, c_l1, r_sub, &rl_sub);
            rs_sub = sign2_sub;
        }
    }
    
    // === 乘法區塊 ===
    // 乘法不需對齊，小數位數相加即可。直接使用原始未 Align 的資料
    char r_mul[MAX_LEN] = {0}; int rl_mul = 0, rs_mul = 1, rdec_mul = 0;
    int r_mul_int[MAX_LEN] = {0}; // 使用 int 陣列防止過程中加總溢位
    rs_mul = sign1 * sign2;
    rdec_mul = dec1 + dec2;
    
    for(int i = 0; i < l1; i++){
        for(int j = 0; j < l2; j++){
            r_mul_int[i+j] += d1[i] * d2[j];
        }
    }
    
    rl_mul = l1 + l2;
    int carry = 0;
    for(int i = 0; i < rl_mul; i++){
        int sum = r_mul_int[i] + carry;
        r_mul[i] = sum % 10;
        carry = sum / 10;
    }
    while(carry > 0){
        r_mul[rl_mul++] = carry % 10;
        carry /= 10;
    }
    
    // === 輸出 ===
    print_bf(rs_add, r_add, rl_add, dec);
    print_bf(rs_sub, r_sub, rl_sub, dec);
    print_bf(rs_mul, r_mul, rl_mul, rdec_mul);
    
    return 0;
}