// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T, int size>
class TPQueue {
 private:
    T arr[size];
    int first, last, count;
 public:
    TPQueue() :first(0), last(0), count(0) {}
    bool isEmpty() const {
        return !count;
    }

    bool isFull() const {
        return (count == size);
    }

    int getPrior(const T& arg) {
        return arg.prior;
    }

    void push(const T& arg) {
        if (isFull()) {
            throw std::string("Full!");
        } else {
            if (isEmpty()) {
                count++;
                int ind = last++ % size;
                arr[ind].ch = arg.ch;
                arr[ind].prior = arg.prior;
            } else {
                int cur = first;
                while (cur < size && getPrior(arr[cur]) > getPrior(arg)) {
                    cur++;
                }
                if (cur == count) {
                    int ind = last++ % size;
                    arr[ind].ch = arg.ch;
                    arr[ind].prior = arg.prior;
                    count++;
                }
                else if (getPrior(arr[cur]) < getPrior(arg)) {
                    int ind = last++ % size;
                    arr[ind].ch = arr[count - 1].ch;
                    arr[ind].prior = arr[count - 1].prior;
                    count++;
                    for (int pos = count - 1; pos > cur; pos--) {
                        arr[pos].ch = arr[pos - 1].ch;
                        arr[pos].prior = arr[pos - 1].prior;
                    }
                    arr[cur].ch = arg.ch;
                    arr[cur].prior = arg.prior;
                }
                else if (getPrior(arr[cur]) == getPrior(arg)) {
                    int ind = last++ % size;
                    arr[ind].ch = arr[count - 1].ch;
                    arr[ind].prior = arr[count - 1].prior;
                    count++;
                    for (int pos = count - 2; pos > cur + 1; pos--) {
                        arr[pos].ch = arr[pos - 1].ch;
                        arr[pos].prior = arr[pos - 1].prior;
                    }
                    cur += 1;
                    arr[cur].ch = arg.ch;
                    arr[cur].prior = arg.prior;
                }
            }
        }
    }

    const T& pop() {
        if (isEmpty()) {
            throw std::string("Empty!");
        } else {
            --count;
            last = first;
            return arr[first++ % size];
        }
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
