#include "restaurant.h"

void khoiTaoDanhSach(Node** head) {
    *head = NULL;
}

int kiemTraTrungMa(Node* head, char* maMon) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.maMon, maMon) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void themMonAn(Node** head, MonAn monMoi) {
    if (kiemTraTrungMa(*head, monMoi.maMon) == 1) {
        printf("Loi: Ma mon [%s] da ton tai! Khong the them.\n", monMoi.maMon);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = monMoi;                    
    newNode->next = NULL;                   

    if (*head == NULL) {
        *head = newNode;
    }   
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; 
        }
        temp->next = newNode;
    }
}

void xoaMonAnTheoMa(Node** head, char* maMon) {
    if (*head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    Node* temp = *head;
    Node* prev = NULL;

    if (strcmp(temp->data.maMon, maMon) == 0) {
        *head = temp->next;
        free(temp);
        printf("Da xoa thanh cong!\n");
        return;
    }

    while (temp != NULL && strcmp(temp->data.maMon, maMon) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay mon an co ma %s!\n", maMon);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Da xoa thanh cong!\n");
}

void xoaMonAnTheoTen(Node** head, char* tenMon) {
    if (*head == NULL) {
        printf("Danh sach rong, khong co mon de xoa!\n");
        return;
    }

    Node* temp = *head;
    Node* prev = NULL;

    if (strcmp(temp->data.tenMon, tenMon) == 0) {
        *head = temp->next;
        free(temp);
        printf("Da xoa thanh cong mon an: %s\n", tenMon);
        return;
    }

    while (temp != NULL && strcmp(temp->data.tenMon, tenMon) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay mon an co ten '%s' de xoa!\n", tenMon);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Da xoa thanh cong mon an: %s\n", tenMon);
}

void capNhatGiaTien(Node* head, char* maMon, int giaMoi) {
    Node* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->data.maMon, maMon) == 0) {
            temp->data.giaTien = giaMoi;
            printf("Da cap nhat gia mon [%s] thanh %d VND!\n", temp->data.tenMon, giaMoi);
            return;
        }
        temp = temp->next;
    }

    printf("Khong tim thay mon an co ma %s de cap nhat!\n", maMon);
}

void hienThiDanhSach(Node* head) {
    if (head == NULL) {
        printf("Danh sach thuc don dang rong!\n");
        return;
    }

    printf("=================== THUC DON NHA HANG ===================\n");
    printf("%-5s | %-10s | %-30s | %-10s\n", "STT", "MA MON", "TEN MON AN", "GIA TIEN");
    printf("---------------------------------------------------------\n");

    Node* temp = head;
    int stt = 1;

    while (temp != NULL) {
        printf("%-5d | %-10s | %-30s | %-10d VND\n", 
               stt, 
               temp->data.maMon, 
               temp->data.tenMon, 
               temp->data.giaTien);
        temp = temp->next;
        stt++;
    }
    printf("=========================================================\n");
}

void docDuLieuTuFile(Node** head, const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", tenFile);
        return;
    }

    MonAn mon;
    while (fscanf(f, "%[^,],%[^,],%d\n", mon.maMon, mon.tenMon, &mon.giaTien) == 3) {
        themMonAn(head, mon);
    }

    fclose(f);
    printf("Da doc du lieu tu file %s vao danh sach!\n", tenFile);
}

void ghiDuLieuRaFile(Node* head, const char* tenFile) {
    FILE* f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("Loi: Khong the mo file %s de ghi!\n", tenFile);
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        fprintf(f, "%s,%s,%d\n", temp->data.maMon, temp->data.tenMon, temp->data.giaTien);
        temp = temp->next;
    }

    fclose(f);
    printf("Da ghi du lieu ra file %s thanh cong!\n", tenFile);
}

void giaiPhongDanhSach(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}