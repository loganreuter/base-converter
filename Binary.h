#ifndef BINARY_H
#define BINARY_H

    #include <vector>
    #include <iterator>
    #include <iostream>

typedef std::vector<uint8_t>::iterator iter;

class Binary
{
private:
    std::vector<uint8_t> binary;
    bool is_signed = 0;

    // void TwosComplement(){
    //     for(int i = 0; i < length; i++){
    //         *binary++ = 1;
    //     }
    // }
    void shrink()
    {
        int size = this->binary.size();

        for (auto i = this->binary.begin(); i < this->binary.end(); i++)
        {
            if (size <= 1 || *i != 0)
                break;

            if (*i == 0)
                this->binary.erase(i);

            size--;
        }
    }

public:
    Binary() {}
    Binary(std::vector<uint8_t> bin){
        this->binary = bin;
    }
    Binary(unsigned int num)
    {
        unsigned int quotient;
        uint8_t remainder;

        while (true)
        {
            quotient = num / 2;
            remainder = num % 2;

            binary.insert(binary.begin(), remainder);

            if (num <= 0)
                break;

            num = quotient;
        }
    }

    void pad(int size)
    {
        for (int i = 0; i < size; i++)
        {
            this->binary.insert(this->binary.begin(), 0);
        }
    }

    size_t get_size() 
    {
        return this->binary.size();
    }

    iter get_begin()
    {
        return this->binary.begin();
    }

    iter get_end()
    {
        return this->binary.end();
    }

    Binary operator+(Binary &b)
    {
        std::vector<uint8_t> ret;

        int diff = b.get_size() - this->binary.size();

        std::cout << "Difference: " << diff << std::endl;

        b.pad((int)((abs(diff) - diff) / 2));
        pad((int)((diff + abs(diff)) / 2));

        std::cout << get_size() << "\t" << b.get_size() << std::endl;

        iter itA = get_end();
        iter itB = b.get_end();
        uint8_t carry = 0;

        while(itA != get_begin()){
            --itA;
            --itB;
            
            uint8_t sum = abs(carry - abs(*itA - *itB));
            carry = (carry && *itA || carry && *itB || carry && *itA && *itB || *itA && *itB);
            std::cout << "itA: " << (int)*itA << "\titB: " << (int)*itB << "\tOut: " << (int)sum << "\tCarry: "<< (int)carry << std::endl;

            ret.insert(ret.begin(), sum);
        }

        b.shrink();
        shrink();

        return Binary(ret);
    }
    
    friend std::ostream &operator<<(std::ostream &os, Binary& b);
};

std::ostream &operator<<(std::ostream &os, Binary &b) {
    for (iter i = b.get_begin(); i < b.get_end(); i++)
    {
        os << (int)*i;
    }
    os << std::endl;
    return os;
}

#endif