#include <iostream>
#include <cassert>
#include <cstddef>
using namespace std;

void print_in_hex(uint8_t byte);
void print_in_hex(const void* data, size_t size);
void print_in_binary(uint8_t byte);
void print_in_binary(const void* data, size_t size);


/**************/
//шестнадцатеричный вид

char nibble_in_hex(uint8_t i){
//    assert(0x0 <= i && i<= 0xf);
    char digits[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    return digits[i];
}

void print_in_hex(uint8_t byte){
    cout << nibble_in_hex(byte >> 4)
         << nibble_in_hex(byte & 0xf);
}

const uint8_t* as_bytes(const void* data);

void print_in_hex(const void* data, size_t size){
    const uint8_t* bytes = as_bytes(data);
    for (size_t i = 0; i < size; i++){
        print_in_hex(bytes[i]);
        if ((i + 1) % 16 == 0){
            cout << "\n";
        }
        else{
            cout << " ";
        }
    }
}

const uint8_t* as_bytes(const void* data){
    return reinterpret_cast<const uint8_t*>(data);
}

/**************/
//двоичный вид

char bit_digit(uint8_t byte, uint8_t bit){
    if (byte & (0x1 << bit)){
        return '1';
    }
    return '0';
}

void print_in_binary(uint8_t byte){
    for(uint8_t bit = 7; bit > 0; bit--){
        cout << bit_digit(byte, bit);
    }
    cout << bit_digit(byte, 0);
}

void print_in_binary(const void* data, size_t size){
    const uint8_t* bytes = as_bytes(data);
    for (size_t i = 0; i < size; i++){
        print_in_binary(bytes[i]);
        if ((i + 1) % 4 == 0){
            cout << "\n";
        }
        else{
            cout << " ";
        }
    }
}

void calc(uint16_t op1,char oper, uint16_t op2){
    //16-й вид
    print_in_hex(&op1, sizeof(op1));
    cout << oper << " ";
    print_in_hex(&op2, sizeof(op2));
    uint16_t result1;
    if (oper == '&'){
        result1 = op1 & op2;
    }
    else
        if (oper == '|'){
            result1 = op1 | op2;
    }
    cout << "= ";
    print_in_hex(&result1, sizeof(result1));
    cout << endl;
    //двоичный вид

    print_in_binary(&op1, sizeof(op1));
    cout << oper << " ";
    print_in_binary(&op2, sizeof(op2));
    uint16_t result2;
    if (oper == '&'){
        result2 = op1 & op2;
    }
    else
        if (oper == '|'){
            result2 = op1 | op2;
        }
    else
        if (oper == '^'){
            result2 = op1 ^ op2;
        }
    print_in_binary(&result2, sizeof(result2));
}

struct Student{
    char name[17];
    uint16_t year;
    float aver;
    uint8_t gender:1;
    uint16_t course;
    Student* starosta;
};

//assert(nibble_to_hex(0x0)=='0');
//assert(nibble_to_hex(0x1)=='1');
//assert(nibble_to_hex(0x2)=='2');
//assert(nibble_to_hex(0x3)=='3');
//assert(nibble_to_hex(0x4)=='4');
//assert(nibble_to_hex(0x5)=='5');
//assert(nibble_to_hex(0x6)=='6');
//assert(nibble_to_hex(0x7)=='7');
//assert(nibble_to_hex(0x8)=='8');
//assert(nibble_to_hex(0x9)=='9');
//assert(nibble_to_hex(0x10)=='10');
//assert(nibble_to_hex(0xa)=='a');
//assert(nibble_to_hex(0xb)=='b');
//assert(nibble_to_hex(0xc)=='c');
//assert(nibble_to_hex(0xd)=='d');
//assert(nibble_to_hex(0xe)=='e');
//assert(nibble_to_hex(0xf)=='f');

int main()
{
    Student Students[3]={
       {"Starosta", 1998, 4, 1, 1, nullptr},
       {"Shubin", 2000, 4, 1, 1},
       {"Borisov", 2000, 4, 1, 1},
    };
    /*********/
    /* адрес и размер массива, всех элементов массива */
    cout << "Address of Students: \t" << &Students << endl;
    cout << "Size of Students: \t" << sizeof(Students) << endl;
    cout << "Address of Students[1]: \t" << &Students[1] << endl;
    cout << "Size of Students[1]: \t" << sizeof(Students[1]) << endl;
    cout << "Address of Students[2]: \t" << &Students[2] << endl;
    cout << "Size of Students[2]: \t" << sizeof(Students[2]) << endl;
    cout << "Address of Students[3]: \t" << &Students[3] << endl;
    cout << "Size of Students[3]: \t" << sizeof(Students[3]) << endl;

    /*********/
    /*адреса полей структуры */
    cout << "Address of name: \t" << &Students[2].name << endl;
    cout << "Address of year: \t" << &Students[2].year << endl;
    cout << "Address of aver: \t" << &Students[2].aver << endl;
    cout << "Address of course: \t" << &Students[2].course << endl;

    /*********/
    /*смещение от начала структуры */
    cout << "Name is at offset: \t" << offsetof(Student, name) << endl;
    cout << "Year is at offset: \t" << offsetof(Student, year) << endl;
    cout << "Aver is at offset: \t" << offsetof(Student, aver) << endl;
    cout << "Course is at offset: \t" << offsetof(Student, course) << endl;

    /*********/
    /*размер полей структуры */
    cout << "Size of name: \t" << sizeof(Students[2].name) << endl;
    cout << "Size of year: \t" << sizeof(Students[2].year) << endl;
    cout << "Size of aver: \t" << sizeof(Students[2].aver) << endl;
    cout << "Size of course: \t" << sizeof(Students[2].course) << endl;

    /*********/
    /*шестнадцатеричное и двоичное представление полей структуры*/
    cout << "Year in hex: \t";
    print_in_hex(&Students[2].year, sizeof(Students[2].year));
    cout << endl;
    cout << "Aver in hex: \t";
    print_in_hex(&Students[2].aver, sizeof(Students[2].aver));
    cout << endl;
    cout << "Course in hex: \t";
    print_in_hex(&Students[2].course, sizeof(Students[2].course));
    cout << endl;

    cout << "Year in bin: \t";
    print_in_binary(&Students[2].year, sizeof(Students[2].year));
    cout << endl;
    cout << "Aver in bin: \t";
    print_in_binary(Students[2].aver);
    cout << endl;
    cout << "Course in bin: \t";
    print_in_binary(Students[2].course);
    cout << endl;


    /*********/
    /*все элементы массива в шестнадцатеричном виде с указанием соответствия блоков байт полям структур */
    cout << "year   aver         course \n";
    for (int i = 0; i < 3; i++){
        print_in_hex(&Students[i].year, sizeof(Students[i].year));
        cout << "|";
        print_in_hex(&Students[i].aver, sizeof(Students[i].aver));
        cout << "|";
        print_in_hex(&Students[i].course, sizeof(Students[i].course));
        cout << endl;
    }



//    uint16_t u1 = 1025;
//    uint16_t u2 = 127;
//    calc(u1, '&', u2);
//    uint32_t u32 = 42;
//    cout << "u32 bytes: ";
//    print_in_hex(&u32, sizeof(u32));
//    cout << "\n";
//    uint16_t u16 = 0x42;
//    cout << "u16 bytes: ";
//    print_in_hex(&u16, sizeof(u16));
//    cout << "\n";
//    uint8_t u8 = 0x42;
//    cout << "u8 bytes: ";
//    print_in_hex(&u8, sizeof(u8));
//    cout << "\n";
//    print_in_binary(&u32, sizeof(u32));
//    cout << "\n";
//    print_in_binary(&u16, sizeof(u16));
//    cout << "\n";
//    print_in_binary(&u8, sizeof(u8));
//    cout << "\n";

}
