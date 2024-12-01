#include <iostream>
#include <cstdio>
#include <cmath>

namespace plotter
{
  unsigned long n;
  double *a, *b, *c;
  FILE* file;

  signed long t1, t2, s1, s2;

  unsigned long Z;

  double f(const double& x, const unsigned long& i)
  { return a[i] * x * x + b[i] * x + c[i]; }

  char gChar(const double& x, const double& y)
  {
    bool tmp = false;

    for (unsigned long i = 0; i < n; i++)
      if (round(f(x, i)*Z)/Z == y) { tmp = true; break; }

    return (tmp) ? '*' : ((x == 0.0) ? ((y == 0.0) ? '+' : '|') : (y == 0.0) ? '-' : ' ' );
  }

  void makeTables()
  {
    for (unsigned long i = 0; i < n; i++)
    { fprintf(file, "+---------- f%02ld ----------+ ", i); }

    fputc('\n', file);

    for (unsigned long i = 0; i < n; i++)
    { fputs("| t          | s          | ", file); }

    fputc('\n', file);

    for (double x = t1; x <= t2; x = (x*Z + 1.0)/Z)
    {
      for (unsigned long i = 0; i < n; i++)
      { fputs("+------------|------------+ ", file); }

      fputc('\n', file);

      for (unsigned long i = 0; i < n; i++)
      { fprintf(file, "| %10.2f | %10.2f | ", x, f(x, i)); }

      fputc('\n', file);
    }

    for (unsigned long i = 0; i < n; i++)
    { fputs("+------------|------------+ ", file); }

    fputs("\n\n\n", file);

    return;
  }

  void plot()
  {
    fputs("       ", file);
    for (double x = t1; x <= t2; x = (x*Z + 1.0)/Z) fputc(' ', file);
    fputs("t\n", file);

    fputs("       ", file);
    
    for (double x = t1; x < 0; x = (x*Z + 1.0)/Z) fputc(' ', file);
    fputs("^\n", file);

    for (double y = s2; y >= s1; y = (y*Z - 1.0)/Z)
    {
      fprintf(file, "%6.2f ", y);

      for (double x = t1; x <= t2; x = (x*Z + 1.0)/Z)
      { fputc(gChar(x, y), file); }

      if (y == 0) fputs("> t\n", file);
      else fputc('\n', file);
    }

    return;
  }

  void colCoef(const unsigned long& i)
  {
    char ctmp;

    std::cout << "Especifique o tipo de funcao (a para MRU, b para MRUV): ";
    std::cin >> ctmp;

    if (ctmp == 'a')
    {
      std::cout << "Especifique v e s_0: ";
      a[i] = 0;
    }
    else if (ctmp == 'b')
    {
      std::cout << "Especifique a, v_0 e s_0: ";
      std::cin >> a[i];
      a[i] /= 2;
    }
    std::cin >> b[i] >> c[i];

    return;
  }

  void colFns()
  {
    char *stmp = new char[20];

    std::cout << "Especifique em que arquivo as funcoes serao plotadas: ";
    std::cin >> stmp;

    file = fopen(stmp, "w");

    std::cout << "Especifique em que intervalo temporal (t1 e t2) as funcoes serao plotadas: ";
    std::cin >> t1 >> t2;

    std::cout << "Especifique em que intervalo espacial (s1 e s2) as funcoes serao plotadas: ";
    std::cin >> s1 >> s2;

    std::cout << "Especifique o multiplicador de zoom com o qual as funcoes serao plotadas: ";
    std::cin >> Z;

    std::cout << "Especifique quantas funcoes serao plotadas: ";
    std::cin >> n;

    a = new double[n]; b = new double[n]; c = new double[n];

    for (unsigned long i = 0; i < n; i++) colCoef(i);
  }

  void intro()
  {
    std::cout << "IAGO ALVES DIAS" << '\n';
    std::cout << "INSTITUTO FEDERAL DA BAHIA - CAMPUS ILHEUS" << '\n';
    std::cout << "INTEGRADO TECNICO EM INFORMATICA 12" << '\n';

    std::cout << "\n";

    std::cout << "Atividade de ILP & FISICA - 2024" << '\n';
    std::cout << "PROFESSOR CIRO & PROFESSOR THIAGO" << '\n';

    std::cout << "\n\n\n";

    std::cout << "Calculadora de Funcoes Fisicas" << '\n';
    std::cout << "Versao 30112024a - Nova" << '\n';

    std::cout << "\n\n\n";

    return;
  }

  void ui()
  {
    bool loop;

    intro();

    do
    {
      colFns();

      makeTables();

      plot();

      fclose(file);

      std::cout << "Continuar? (1 para sim, 0 para nao): ";
      std::cin >> loop;
    }
    while (loop);

    return;
  }
}

signed main()
{
  plotter::ui();
  return 0;
}
