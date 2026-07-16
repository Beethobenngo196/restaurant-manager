#include "../include/restaurant.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*=========================================================
    CAC HAM HO TRO NOI BO (STATIC HELPER FUNCTIONS)
=========================================================*/

static void inTieuDeBang(void)
{
    printf("%-10s | %-30s | %-15s\n",
           "MA MON",
           "TEN MON AN",
           "GIA TIEN (VND)");
    printf("-----------------------------------------------------------\n");
}

/*
 * Ham in 1 mon an
 */
void inMonAn(MonAn mon)
{
    printf("%-10s | %-30s | %-15d VND\n", mon.maMon, mon.tenMon, mon.giaTien);
}

static void hoanDoiMonAn(Node* a, Node* b)
{
    MonAn temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/*=========================================================
    KHUI TAO & KIEM TRA DU LIEU (INIT & VALIDATION)
=========================================================*/

/*
 * Khoi tao danh sach lien ket rong
 */
void khoiTaoDanhSach(Node** head)
{
    *head = NULL;
}

/*
 * Kiem tra ma mon an da ton tai trong danh sach hay chua
 * Tra ve 1 neu ton tai, 0 neu chua
 */
int kiemTraTrungMa(Node* head, char* maMon)
{
    Node* temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->data.maMon, maMon) == 0)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

/*=========================================================
    THAO TAC THEM & XOA (INSERT & DELETE)
=========================================================*/

/*
 * Them mot mon an moi vao cuoi danh sach
 */
void themMonAn(Node** head, MonAn monMoi)
{
    if (kiemTraTrungMa(*head, monMoi.maMon) == 1)
    {
        printf("Loi: Ma mon [%s] da ton tai! Khong the them.\n", monMoi.maMon);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = monMoi;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node* temp = *head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

/*
 * Xoa mon an ra khoi danh sach theo ma mon
 */
void xoaMonAnTheoMa(Node** head, char* maMon)
{
    if (*head == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }

    Node* temp = *head;
    Node* prev = NULL;

    if (strcmp(temp->data.maMon, maMon) == 0)
    {
        *head = temp->next;
        free(temp);
        printf("Da xoa thanh cong!\n");
        return;
    }

    while (temp != NULL && strcmp(temp->data.maMon, maMon) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Khong tim thay mon an co ma %s!\n", maMon);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Da xoa thanh cong!\n");
}

/*
 * Xoa mon an ra khoi danh sach theo ten mon
 */
void xoaMonAnTheoTen(Node** head, char* tenMon)
{
    if (*head == NULL)
    {
        printf("Danh sach rong, khong co mon de xoa!\n");
        return;
    }

    Node* temp = *head;
    Node* prev = NULL;

    if (strcmp(temp->data.tenMon, tenMon) == 0)
    {
        *head = temp->next;
        free(temp);
        printf("Da xoa thanh cong mon an: %s\n", tenMon);
        return;
    }

    while (temp != NULL && strcmp(temp->data.tenMon, tenMon) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Khong tim thay mon an co ten '%s' de xoa!\n", tenMon);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Da xoa thanh cong mon an: %s\n", tenMon);
}

/*=========================================================
    CAP NHAT & HIEN THI DU LIEU (UPDATE & DISPLAY)
=========================================================*/

/*
 * Cap nhat gia tien cua mot mon an theo ma
 */
void capNhatGiaTien(Node* head, char* maMon, int giaMoi)
{
    Node* temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->data.maMon, maMon) == 0)
        {
            temp->data.giaTien = giaMoi;
            printf("Da cap nhat gia mon [%s] thanh %d VND!\n", temp->data.tenMon, giaMoi);
            return;
        }

        temp = temp->next;
    }

    printf("Khong tim thay mon an co ma %s de cap nhat!\n", maMon);
}

/*
 * In toan bo thuc don nha hang ra man hinh
 */
void hienThiDanhSach(Node* head)
{
    if (head == NULL)
    {
        printf("Danh sach thuc don dang rong!\n");
        return;
    }

    printf("=================== THUC DON NHA HANG ===================\n");
    printf("%-5s | %-10s | %-30s | %-10s\n", "STT", "MA MON", "TEN MON AN", "GIA TIEN");
    printf("---------------------------------------------------------\n");

    Node* temp = head;
    int stt = 1;

    while (temp != NULL)
    {
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

/*=========================================================
    XU LY FILE & QUAN LY BO NHO (FILE I/O & MEMORY)
=========================================================*/

/*
 * Doc du lieu mon an tu file text vao danh sach
 */
void docDuLieuTuFile(Node** head, const char* tenFile)
{
    FILE* f = fopen(tenFile, "r");

    if (f == NULL)
    {
        printf("Loi: Khong the mo file %s de doc!\n", tenFile);
        return;
    }

    MonAn mon;

    while (fscanf(f, "%[^,],%[^,],%d\n", mon.maMon, mon.tenMon, &mon.giaTien) == 3)
    {
        themMonAn(head, mon);
    }

    fclose(f);
    printf("Da doc du lieu tu file %s vao danh sach!\n", tenFile);
}

/*
 * Ghi toan bo danh sach mon an ra file text
 */
void ghiDuLieuRaFile(Node* head, const char* tenFile)
{
    FILE* f = fopen(tenFile, "w");

    if (f == NULL)
    {
        printf("Loi: Khong the mo file %s de ghi!\n", tenFile);
        return;
    }

    Node* temp = head;

    while (temp != NULL)
    {
        fprintf(f, "%s,%s,%d\n", temp->data.maMon, temp->data.tenMon, temp->data.giaTien);
        temp = temp->next;
    }

    fclose(f);
    printf("Da ghi du lieu ra file %s thanh cong!\n", tenFile);
}

/*
 * Giai phong toan bo bo nho cua danh sach lien ket
 */
void giaiPhongDanhSach(Node* head)
{
    Node* temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*=========================================================
    [DA BO SUNG]: MODULE TIM KIEM LIEN KET (SEARCHING)
    (Chuyen tu hoang.c ve phat.c cho dung ban chat Node*)
=========================================================*/

/*
 * Tim kiem theo ten mon tren Linked List
 */
void timKiemTheoTen(Node* head, char* tenMon)
{
    if (head == NULL)
    {
        printf("Danh sach rong.\n");
        return;
    }

    Node* p = head;
    int timThay = 0;

    printf("\n========== KET QUA TIM KIEM THEO TEN ==========\n");

    while (p != NULL)
    {
        if (strcmp(p->data.tenMon, tenMon) == 0)
        {
            if (!timThay)
            {
                inTieuDeBang();
            }

            inMonAn(p->data);
            timThay = 1;
        }

        p = p->next;
    }

    if (!timThay)
    {
        printf("Khong tim thay mon \"%s\".\n", tenMon);
    }
}

/*
 * Tim kiem theo khoang gia tren Linked List
 */
void timKiemTheoKhoangGia(Node* head, int giaMin, int giaMax)
{
    if (head == NULL)
    {
        printf("Danh sach rong.\n");
        return;
    }

    Node* p = head;
    int timThay = 0;

    if (giaMin > giaMax)
    {
        int temp = giaMin;
        giaMin = giaMax;
        giaMax = temp;
    }

    printf("\n======= KET QUA TIM KIEM THEO GIA =======\n");

    while (p != NULL)
    {
        if (p->data.giaTien >= giaMin && p->data.giaTien <= giaMax)
        {
            if (!timThay)
            {
                inTieuDeBang();
            }

            inMonAn(p->data);
            timThay = 1;
        }

        p = p->next;
    }

    if (!timThay)
    {
        printf("Khong co mon nao trong khoang gia %d - %d.\n",
               giaMin,
               giaMax);
    }
}

/*=========================================================
    MODULE SAP XEP DANH SACH LIEN KET (SORTING)
=========================================================*/

/*
 * Sap xep thuc don theo MA MON (1: Tang dan | 0: Giam dan)
 */
void sapXepTheoMa(Node** head, int tangDan)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL) return;

    for (Node* p = *head; p != NULL; p = p->next)
    {
        for (Node* q = p->next; q != NULL; q = q->next)
        {
            int cmp = strcmp(p->data.maMon, q->data.maMon);
            if ((tangDan && cmp > 0) || (!tangDan && cmp < 0))
            {
                hoanDoiMonAn(p, q);
            }
        }
    }
}

/*
 * Sap xep thuc don theo TEN MON (1: Tang dan | 0: Giam dan)
 */
void sapXepTheoTen(Node** head, int tangDan)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL) return;

    for (Node* p = *head; p != NULL; p = p->next)
    {
        for (Node* q = p->next; q != NULL; q = q->next)
        {
            int cmp = strcmp(p->data.tenMon, q->data.tenMon);
            if ((tangDan && cmp > 0) || (!tangDan && cmp < 0))
            {
                hoanDoiMonAn(p, q);
            }
        }
    }
}

/*
 * Sap xep thuc don theo GIA TIEN (1: Tang dan | 0: Giam dan)
 */
void sapXepTangTheoGia(Node** head, int tangDan)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL) return;

    for (Node* p = *head; p != NULL; p = p->next)
    {
        for (Node* q = p->next; q != NULL; q = q->next)
        {
            if ((tangDan && p->data.giaTien > q->data.giaTien) ||
                (!tangDan && p->data.giaTien < q->data.giaTien))
            {
                hoanDoiMonAn(p, q);
            }
        }
    }
}