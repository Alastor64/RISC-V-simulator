#include "Port.hpp"
#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
PortWrite::PortWrite(Register *_, cw &_size, cw &_maxCount)
    : file(_), size(_size), maxCount(_maxCount) {
    count = 0;
}
void PortWrite::write(cw &index, cw &value) {
    count++;
    if (count > maxCount) {
        throw "too many port write!";
    }
    if (index < size) {
        file[index].write(value);
    }
}
void PortWrite::update() { count = 0; }
PortOr::PortOr(Register *_, cw &_size) : file(_), size(_size) { count = 0; }
void PortOr::write(cw &_index, cw &_value) {
    if (_index > size) {
        throw "you may not write a inexist register in port_or";
    }
    index[count] = _index;
    value[count] = _value;
    count++;
    if (count > 2) {
        throw "too many port_or write";
    }
}
void PortOr::update() {
    switch (count) {
    case 0:
        break;
    case 1:
        file[index[0]].write(value[0]);
        break;
    case 2:
        if (index[0] == index[1]) {
            file[index[0]].write(value[0] | value[1]);
        } else {
            for (int i = 0; i < 2; i++) {
                file[index[i]].write(value[i]);
            }
        }
        break;
    default:
        throw "unexpected error in port_or update";
    }
    count = 0;
}
PortRead::PortRead(Register const *_, cw &_size) : file(_), size(_size) {}
word PortRead::read(cw &index) const {
    if (index < size) {
        return file[index].getv();
    } else {
        throw "you may not read a inexist reg";
        // return 0;
    }
}
void PortRead::update() {}

PortROBtl::PortROBtl(Register *_tl, Register *_gene) : tl(_tl), gene(_gene) {
    count = 0;
}
void PortROBtl::add(cw &x) {
    if (count) {
        throw "too many add in Port ROB";
    }
    count++;
    cw tl_nxt = tl->getv() + x;
    if (tl_nxt >= ROB_SIZE) {
        tl->write(tl_nxt & getLF1(ROB_SIZE_WIDTH));
        gene->write((gene->getv() + 1) & 3);
    } else {
        tl->write(tl_nxt);
    }
}
void PortROBtl::update() { count = 0; }