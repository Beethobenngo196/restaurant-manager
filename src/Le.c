#include "restaurant.h"

/*=========================================================
    CAC HAM NOI BO (STATIC HELPER FUNCTIONS)
=========================================================*/

/*
 * Tao mot OrderNode moi cho hang doi (Co so luong mon)
 */
static OrderNode* taoOrderNode(MonAn mon, int soLuong)
{
    OrderNode* node = (OrderNode*)malloc(sizeof(OrderNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->data = mon;
    node->soLuong = soLuong;
    node->next = NULL;

    return node;
}

/*
 * Tao mot StackNode moi cho ngan xep hoan tac
 */
static StackNode* taoStackNode(LoaiThaoTac loai, MonAn mon)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->loai = loai;
    node->thongTinCu = mon;
    node->next = NULL;

    return node;
}

/*
 * Tao mot HistoryNode moi cho danh sach lien ket kep (Co prev/next)
 */
static HistoryNode* taoHistoryNode(char* description)
{
    HistoryNode* node = (HistoryNode*)malloc(sizeof(HistoryNode));

    if (node == NULL)
    {
        return NULL;
    }

    time_t t = time(NULL);
    struct tm* tmInfo = localtime(&t);
    strftime(node->timestamp, sizeof(node->timestamp), "%H:%M", tmInfo);

    strcpy(node->description, description);
    node->next = NULL;
    node->prev = NULL;

    return node;
}

/*=========================================================
    QUEUE MODULE (QUAN LY DON HANG - FIFO)
=========================================================*/

/*
 * Them don hang vao cuoi hang doi
 */
void enqueueOrder(OrderNode** front, OrderNode** rear, MonAn mon, int soLuong)
{
    OrderNode* newNode = taoOrderNode(mon, soLuong);

    if (newNode == NULL)
    {
        return;
    }

    if (*front == NULL)
    {
        *front = *rear = newNode;
    }
    else
    {
        (*rear)->next = newNode;
        *rear = newNode;
    }

    printf("Da nhan don hang: [%s] (SL: %d) vao hang doi nha kitchen.\n", mon.tenMon, soLuong);
}

/*
 * Phuc vu don hang o dau hang doi
 */
void dequeueOrder(OrderNode** front, OrderNode** rear)
{
    if (*front == NULL)
    {
        printf("Hang doi order trong, khong co don hang can phuc vu!\n");
        return;
    }

    OrderNode* temp = *front;
    long long thanhTien = (long long)temp->data.giaTien * temp->soLuong;

    printf("-> [FIFO] Dang phuc vu mon: %-25s | SL: %-3d | Thanh tien: %lld VND\n",
           temp->data.tenMon,
           temp->soLuong,
           thanhTien);

    *front = (*front)->next;

    if (*front == NULL)
    {
        *rear = NULL;
    }

    free(temp);
}

/*=========================================================
    STACK MODULE (QUAN LY HOAN TAC - LIFO)
=========================================================*/

/*
 * Them thao tac vao ngan xep hoan tac
 */
void pushUndo(StackNode** top, LoaiThaoTac loai, MonAn mon)
{
    StackNode* newNode = taoStackNode(loai, mon);

    if (newNode == NULL)
    {
        return;
    }

    newNode->next = *top;
    *top = newNode;
}

/*
 *  Hoan tac thao tac cuoi cung trong ngan xep
 */
void popUndo(StackNode** top, Node** headMainList)
{
    if (*top == NULL)
    {
        printf("Khong co thao tac nao de hoan tac (Undo Stack trong)!\n");
        return;
    }

    StackNode* temp = *top;
    *top = (*top)->next;

    printf("-> [UNDO] Dang hoan tac thao tac: ");

    if (temp->loai == THEM)
    {
        printf("Xoa mon vua THEM [%s - %s]\n", temp->thongTinCu.maMon, temp->thongTinCu.tenMon);
        /* Thao tác ngược lại của THÊM là XÓA món đó đi khỏi danh sách chính */
        xoaMonAnTheoMa(headMainList, temp->thongTinCu.maMon);
    }
    else if (temp->loai == XOA)
    {
        printf("Khoi phuc mon vua XOA [%s - %s]\n", temp->thongTinCu.maMon, temp->thongTinCu.tenMon);
        /* Thao tác ngược lại của XÓA là THÊM lại món đó vào danh sách chính */
        themMonAn(headMainList, temp->thongTinCu);
    }
    else if (temp->loai == SUA)
    {
        printf("Khoi phuc gia cu cua mon [%s] ve %d VND\n", temp->thongTinCu.tenMon, temp->thongTinCu.giaTien);
        /* Thao tác ngược lại của SỬA là CẬP NHẬT lại giá tiền cũ */
        capNhatGiaTien(*headMainList, temp->thongTinCu.maMon, temp->thongTinCu.giaTien);
    }

    free(temp);
}

/*=========================================================
    DOUBLY LINKED LIST MODULE (NHAT KY HOAT DONG)
=========================================================*/

/*
 * Them nhat ky vao cuoi danh sach lien ket kep (Co prev/next)
 */
void addHistory(HistoryNode** head, HistoryNode** tail, char* description)
{
    HistoryNode* newNode = taoHistoryNode(description);

    if (newNode == NULL)
    {
        return;
    }

    if (*head == NULL)
    {
        *head = *tail = newNode;
    }
    else
    {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

/*
 * Ghi nhat ky hoat dong ra file text
 */
void ghiFileHistory(HistoryNode* head, const char* tenFile)
{
    FILE* f = fopen(tenFile, "w");

    if (f == NULL)
    {
        printf("Loi: Khong the mo file %s de ghi!\n", tenFile);
        return;
    }

    HistoryNode* p = head;

    while (p != NULL)
    {
        fprintf(f, "[%s] %s\n", p->timestamp, p->description);
        p = p->next;
    }

    fclose(f);
    printf("Da ghi nhat ky hoat dong vao file %s thanh cong!\n", tenFile);
}

/*=========================================================
    STATISTICS & MEMORY MANAGEMENT MODULE
=========================================================*/

/*
 * Tinh tong doanh thu tu hang doi don hang da phuc vu
 */
long long tinhTongDoanhThu(OrderNode* queueDaPhucVu)
{
    long long tongDoanhThu = 0;
    OrderNode* p = queueDaPhucVu;

    while (p != NULL)
    {
        tongDoanhThu += (long long)p->data.giaTien * p->soLuong;
        p = p->next;
    }

    return tongDoanhThu;
}

/*
 * Tinh gia tien trung binh cua thuc don
 */
double tinhGiaTrungBinhMenu(Node* head)
{
    long long tongGiaTien = 0;
    int soMonAn = 0;
    Node* p = head;

    while (p != NULL)
    {
        tongGiaTien += p->data.giaTien;
        soMonAn++;
        p = p->next;
    }

    if (soMonAn == 0)
    {
        return 0.0;
    }

    return (double)tongGiaTien / soMonAn;
}

/*
 * In bang thong ke tong hop
 */
void thongKeDuLieu(OrderNode* queueHead, Node* menuHead)
{
    long long tongDoanhThu = tinhTongDoanhThu(queueHead);
    double giaTrungBinh = tinhGiaTrungBinhMenu(menuHead);

    printf("\n========== THONG KE DU LIEU HOAT DONG ==========\n");
    printf("Tong doanh thu cac don hang : %lld VND\n", tongDoanhThu);
    printf("Gia trung binh moi mon menu   : %.2f VND\n", giaTrungBinh);
    printf("================================================\n");
}

/*
 * Giai phong bo nho hang doi Queue
 */
void giaiPhongQueue(OrderNode** front)
{
    OrderNode* p = *front;

    while (p != NULL)
    {
        OrderNode* temp = p;
        p = p->next;
        free(temp);
    }

    *front = NULL;
}

/*
 * Giai phong bo nho ngan xep Stack
 */
void giaiPhongStack(StackNode** top)
{
    StackNode* p = *top;

    while (p != NULL)
    {
        StackNode* temp = p;
        p = p->next;
        free(temp);
    }

    *top = NULL;
}

/*
 * Giai phong bo nho danh sach kep History
 */
void giaiPhongHistory(HistoryNode** head)
{
    HistoryNode* p = *head;

    while (p != NULL)
    {
        HistoryNode* temp = p;
        p = p->next;
        free(temp);
    }

    *head = NULL;
}

/*
 * Giai phong toan bo Module 2
 */
void giaiPhongModule2(OrderNode** queueHead, StackNode** undoTop, HistoryNode** historyHead)
{
    giaiPhongQueue(queueHead);
    giaiPhongStack(undoTop);
    giaiPhongHistory(historyHead);
}