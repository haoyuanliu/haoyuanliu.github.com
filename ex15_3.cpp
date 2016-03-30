#include <iostream>
#include <string>
using namespace std;
class Quote
{
    public:
        Quote() = default;
        Quote(const string &s, double p) : bookNo(s), price(p) {}
        string isbn() const
        {
            return bookNo;
        }
        virtual double net_price(size_t n) const 
        {
            return price * n;
        }
        virtual ~Quote() = default;
    private:
        string bookNo;
    protected:
        double price = 0.0;
};
class Bulk_quote : public Quote
{
    public:
        double net_price(size_t n) const override;
};

double print_total(ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << "# sold: " << n << " total due:" << ret << endl;
    return ret;
}
int main()
{
    return 0;
}
