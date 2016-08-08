template <class ElemType>
class example1
{
public:
    example1( ElemType min, ElemType max ) {};
    example1( const ElemType *array, int size ) {};
    ElemType& operator[]( int index ) {};
    bool operator==( const example1& ) const {};
    bool insert( const ElemType*, int );
    bool insert( ElemType ) {return true;};
    ElemType min() const { return _min; };
    ElemType max() const { return _max; };
    void min( ElemType );
    void max( ElemType );
    int count( ElemType value ) const;
private:
    int size;
    ElemType *parray;
    ElemType _min;
    ElemType _max;
};

void main()
{
    example1<double> a(1.2, 3.4);
    a.insert(7.8);
}