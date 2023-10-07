#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
struct polynomial
{
    int degree;
    float* constants;
};
void load(ifstream* file, polynomial& P)
{
    char extra;
    *file >> P.degree;
    *file >> extra;
    P.constants = new float[P.degree + 1]{};
    for (int i = 0; i <= P.degree; i++)
    {
        *file >> P.constants[i];
    }
}
void print(polynomial P)
{
    cout << P.degree;
    cout << ":";
    for (int i = 0; i <= P.degree; i++)
    {
        if (P.constants[i]!=0)
        {
            cout << P.constants[i];
            if (P.degree - i != 0)
            {
                cout << "x";
            }
            if (P.degree - i > 1)
            {
                cout <<"^" << P.degree - i;
            }
            if (i != P.degree)
            {
                if (P.constants[i + 1] > 0)
                {
                    cout << "+";
                }
            }
            
        }
        else if (P.constants[i + 1] > 0)
        {
            cout << "+";
        }
        
        
    }
}
polynomial product(polynomial a, polynomial b)
{
    polynomial product_pol;

    product_pol.degree = a.degree + b.degree;

    
    product_pol.constants = new float [product_pol.degree + 1]{};

    for (int j = a.degree; j >= 0; j--)
    {
        for (int k = b.degree; k >= 0; k--)
        {
            product_pol.constants[j + k] += a.constants[j] * b.constants[k];
        }
    }
    return  product_pol;
}
polynomial add(polynomial a, polynomial b)
{
    polynomial s;
    polynomial l;
    polynomial add_pol;
    if (a.degree > b.degree)
    {
        add_pol.degree = a.degree;
        s = b;
        l = a;
    }
    else
    {
        add_pol.degree = b.degree;
        s = a;
        l = b;
    }
        
    add_pol.constants = new float[add_pol.degree + 1]{};
    for(int i= add_pol.degree,j=s.degree;i>=0;i--,j--)
    {
        if (j >= 0)
        {
            add_pol.constants[i] = l.constants[i] + s.constants[j];
        }
        else
            add_pol.constants[i] = l.constants[i];
        
    }
    polynomial zero;
    zero.degree=0;
    zero.constants=new float[zero.degree+1];
    int j=0;
    while(add_pol.constants[j]==0)
    {
        j++;
        if(j>add_pol.degree)
        {
            return zero;
        }
    }
    polynomial x;
    x.degree=add_pol.degree-j;
    x.constants=new float[x.degree+1];
    int i=add_pol.degree;
    while(i>=j)
    {
        x.constants[i-j]=add_pol.constants[i];
        i--;
    }
    return x;
}
polynomial sub(polynomial a, polynomial b)
{
    for (int i = b.degree; i >= 0; i--)
    {
        b.constants[i] *= -1;
    }
    return add(a, b);
}
int pol_eval(polynomial a,int val)
{
    int sum=0;
    for(int i=a.degree;i>=0;i--)
    {
        sum+=a.constants[i]*pow(val,a.degree-i);
    }
    return sum;
}
polynomial differentiation(polynomial a)
{
    polynomial differenced;
    differenced.degree=a.degree-1;
    differenced.constants=new float[differenced.degree+1];
    differenced.constants[differenced.degree]=a.constants[a.degree-1];
    for(int i=a.degree-2,j=differenced.degree-1;i>=0;i--,j--)
    {
        differenced.constants[j]=(a.degree-i)*a.constants[i];
    }
    return differenced;
}
polynomial integration(polynomial a)
{
    polynomial integrated;
    integrated.degree=a.degree+1;
    integrated.constants=new float[integrated.degree+1];
    integrated.constants[integrated.degree]=0;
    
    for(int i=a.degree,j=integrated.degree-1;i>=0;i--,j--)
    {
        integrated.constants[j]=a.constants[i]/(a.degree-j+1);
    }
    return integrated;
}
float integralfinder(polynomial a,int lower,int upper)
{
    polynomial b;
    b=integration(a);
    return pol_eval(b,upper)-pol_eval(b,lower);
}
void divider(polynomial dividend,polynomial divisor,polynomial &quotient,polynomial &remaind)
{
    quotient.degree=dividend.degree-divisor.degree;
    quotient.constants=new float[quotient.degree+1]{};
    //.............................................
    polynomial quotient_fake;
    quotient_fake.degree=dividend.degree-divisor.degree;
    quotient_fake.constants=new float[quotient_fake.degree+1]{};
    //............................................
    remaind.degree=dividend.degree;
    remaind.constants=new float[remaind.degree+1]{};
    //.............................................
    int i=0;
    while(dividend.degree!=0 && dividend.degree>=divisor.degree)
    {
        for(int i=0;i<=quotient_fake.degree;i++)
        {
            quotient_fake.constants[i]=0;
        }
        //.............................................
        quotient_fake.constants[i]=dividend.constants[0]/divisor.constants[0];
        quotient.constants[i]=quotient_fake.constants[i];
        dividend=sub(dividend,product(quotient_fake,divisor));
        i++;

    }
    remaind=dividend;
}
int main()
{
    int q = 0;

    cout << "1 for product\n";
    cout << "2 for Addition\n";
    cout << "3 for Substraction\n";
    cout << "4 for value evaluator\n";
    cout << "5 for Differentiation\n";
    cout << "6 for Integration\n";
    cout << "7 for Integral\n";
    cout << "8 for Division\n";
    while (q != -1)
    {
        cin >> q;
        if (q == 1)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            polynomial pro_pol;
            pro_pol = product(pols[0], pols[1]);
            cout << "After Product\n";
            print(pro_pol);
            cout << "\n";
        }
        else if (q == 2)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            polynomial add_pol;
            add_pol = add(pols[0], pols[1]);
            cout << "After Adding\n";
            print(add_pol);
            cout << "\n";
        }
        else if (q == 3)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            polynomial sub_pol;
            sub_pol = sub(pols[0], pols[1]);
            cout << "After subtracting\n";
            print(sub_pol);
            cout << "\n";
        }
        else if (q == 4)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            int evaluated_value;
            int val;
            file>>val;
            for(int i=0;i<num_of_pols;i++)
            {
                cout << "Polynomial no "<<i+1<<" at "<<val<<" is ";
                evaluated_value=pol_eval(pols[i],val);
                cout<<evaluated_value;
                cout << "\n";    
            }
            
        }
        else if (q == 5)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            polynomial differenced;
            for(int i=0;i<num_of_pols;i++)
            {
                cout << "differentiation of Polynomial no "<<i+1<<" is ";
                differenced=differentiation(pols[i]);
                print(differenced);
                cout << "\n";    
            }
            
        }
        else if (q == 6)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            polynomial integrated;
            for(int i=0;i<num_of_pols;i++)
            {
                cout << "Integration of Polynomial no "<<i+1<<" is ";
                integrated=integration(pols[i]);
                print(integrated);
                cout << "\n";    
            }
            
        }
        else if (q == 7)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            float integral;
            int upper,lower;
            cout<<"Enter lower and upper limit : ";
            cin>>lower>>upper;
            for(int i=0;i<num_of_pols;i++)
            {
                cout << "Integral of Polynomial no "<<i+1<<" in range {"<<lower<<","<<upper<<"} is ";
                integral=integralfinder(pols[i],lower,upper);
                cout<<integral;
                cout << "\n";    
            }
            
        }
           else if (q == 8)
        {
            ifstream file("inputs.txt");
            polynomial* pols;
            int num_of_pols;
            file >> num_of_pols;
            pols = new polynomial[num_of_pols];
            for (int i = 0; i < num_of_pols; i++)
            {
                load(&file, pols[i]);
            }
            for (int i = 0; i < num_of_pols; i++)
            {
                print(pols[i]);
                cout << "\n";
            }
            polynomial quotient;
            polynomial remaind;
            for(int i=0;i<num_of_pols;i++)
            {
                cout << "\n";    
            }
            divider(pols[0],pols[1],quotient,remaind);
            cout<<"QUOTIENT : ";
            print(quotient);
            cout<<"\nREMAINDER : ";
            if(remaind.degree==0)
            {
                cout<<"0";
            }
            else
                print(remaind);
        }
        else if (q == -1)
        {
            cout << "program ended";
        }
        else
        {
            cout << "wrong input";
        }
    }
   
    return 0;
}
