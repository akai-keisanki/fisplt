// g++ .\src\fisplt.cpp -o .\bin\fisplt.exe

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

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
    for (double x = t1; x < 0; x = (x*Z + 1.0)/Z) fputc(' ', file);
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

  void colCoef(const unsigned long& i, FILE* ftmp)
  {
    char stmp[5];

    fscanf(ftmp, "funcao %s\n", stmp);

    if (strcmp(stmp, "mruv") == 0)
    {
      fscanf(ftmp, "s = %lf + %lft + %lft^2/2\n", c + i, b + i, a + i);
      a[i] /= 2;
    }
    else if (strcmp(stmp, "mru") == 0)
    {
      fscanf(ftmp, "s = %lf + %lft\n", c + i, b + i);
      a[i] = 0;
    }
    else
      std::cout << "Uma funcao nao pode ser interpretada" << '\n';

    return;
  }

  void colFns()
  {
    FILE* ftmp;

    ftmp = fopen("instrucoes.txt", "w");

    fputs("plotar em (arquivo).txt\n", ftmp);
    fputs("(n : unsigned int) funcoes\n", ftmp);
    fputs("plotar t em [(t_1 : int) .. (t_2 : int)]\n", ftmp);
    fputs("plotar s em [(s_1 : int) .. (s_2 : int)]\n", ftmp);
    fputs("ampliar (z : unsigned int)x\n", ftmp);
    fputs("funcao (mru/mruv)\n", ftmp);
    fputs("(\"s = (s_0) + (v)t\" se mru, \"s = (s_0) + (v_0)t + (a)t^2/2\" se mruv. Descreva em decimais com ponto, deixe os sinais de soma e adicione o menos colado em numeros negativos.)\n", ftmp);
    fputs("(continue a partir de `funcao ...` até ter n funcoes)", ftmp);

    fclose(ftmp);

    char* stmp = new char[30];
    std::cout << "Edite `instrucoes.txt`, substitua tudo entre parênteses e entre qualquer coisa ao terminar. > ";
    std::cin >> stmp;

    ftmp = fopen("instrucoes.txt", "r");

    fscanf(ftmp, "plotar em %s\n", stmp);

    file = fopen(stmp, "w");

    fscanf(ftmp, "%lu funcoes\n", &n);

    fscanf(ftmp, "plotar t em [%ld .. %ld]\n", &t1, &t2);

    fscanf(ftmp, "plotar s em [%ld .. %ld]\n", &s1, &s2);

    fscanf(ftmp, "ampliar %lux\n", &Z);

    a = new double[n]; b = new double[n]; c = new double[n];

    for (unsigned long i = 0; i < n; i ++) colCoef(i, ftmp);

    fclose(ftmp);
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
