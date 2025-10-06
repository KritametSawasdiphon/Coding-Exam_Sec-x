#include <stdio.h>

// ฟังก์ชันคืนค่าอัตราค่าจ้างต่อชั่วโมงตามระดับรายได้
float gatHourlyRate(char Leval) {
    switch (Leval) {
        case 'L': return 100.0;
        case 'M': return 200.0;
        case 'H': return 300.0;
        default: return 0.0;  // กรณีไม่ตรงกับ L, M, H
    }
}

// ฟังก์ชันคำนวณจำนวนชั่วโมง OT รวม
float calculate(float OThours[], int days) {
    float total = 0.0;
    for (int i = 0; i < days; i++) {
        total += OThours[i];
    }
    return total;
}

// ฟังก์ชันคืนอัตราภาษีหัก ณ ที่จ่ายตามระดับรายได้
float calculatDeductionRate(char Leval) {
    switch (Leval) {
        case 'L': return 0.10;  // 10%
        case 'M': return 0.20;  // 20%
        case 'H': return 0.25;  // 25%
        default: return 0.0;
    }
}

// ฟังก์ชันคำนวณรายได้สุทธิหลังหักภาษี
float calculateNetIncome(float gross ,float deductionRate) {
    return gross * (1 - deductionRate);
}

int main() {
    int days;
    float OThours[10];
    char incomLeval;
    float total_OT, hourly_rate, gross_income, net_income, deductionRate;

    printf("*** OT and Tax Calculator ***\n");

    // รับจำนวนวัน OT
    do {
        printf("Enter number of OT days (1-10): ");
        scanf("%d", &days);
    } while (days < 1 || days > 10);

    // รับชั่วโมง OT รายวัน
    for (int i = 0; i < days; i++) {
        printf("Enter OT hours for day %d: ", i + 1);
        scanf("%f", &OThours[i]);
        if (i < days - 1) printf("...(input continues)...\n");
    }

    // รับระดับรายได้
    printf("Enter Income Level (L, M, H): ");
    scanf(" %c", &incomLeval);  // เพิ่ม space หน้า %c เพื่อเคลียร์ buffer

    // คำนวณ
    hourly_rate = gatHourlyRate(incomLeval);
    if (hourly_rate == 0.0) {
        printf("Invalid Income Level entered.\n");
        return 1;
    }

    total_OT = calculate(OThours, days);
    gross_income = total_OT * hourly_rate;
    deductionRate = calculatDeductionRate(incomLeval);
    net_income = calculateNetIncome(gross_income, deductionRate);

    // แสดงผลลัพธ์
    printf("\n--- Income Summary ---\n");
    printf("Total OT Hours        : %.2f hours\n", total_OT);
    printf("Hourly Rate           : %.2f\n", hourly_rate);
    printf("Gross OT Income       : %.2f\n", gross_income);
    printf("Deduction Rate        : %.0f%%\n", deductionRate * 100);
    printf("Net Income After Tax  : %.2f\n", net_income);

    return 0;
}
