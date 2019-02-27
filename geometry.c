#include <math.h>

#include "geometry.h"

int verify(point p, point a, point b) {

  //Verifica se os pontos a e b são iguais, caso sim retorna 0
  if (a.x - b.x == 0 && a.y - b.y == 0) {
    if (p.y == a.y && p.x == a.x) { //verifica se o ponto p está em cima de ab
      return 2;
    }
    return 0;
  }

  //Checa se o ponto p esta diretamente no segmento AB
  int crossproduct = (p.y - a.y) * (b.x - a.x) - (p.x - a.x) * (b.y - a.y);
  int dotproduct = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
  int squaredlengthba = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
  if (crossproduct == 0 && dotproduct >= 0 && dotproduct <= squaredlengthba) {
    return 2;
  }

  //define o ponto de destino do raio
  point end_ray;
  end_ray.y = p.y;
  end_ray.x = p.x + 2000;

  //checa se um raio disparado a direita colide com a aresta
  float d = (end_ray.x - p.x) * (b.y - a.y) - (end_ray.y - p.y) * (b.x - a.x);
  float u = ((a.x - p.x) * (end_ray.y - p.y) - (a.y - p.y) * (end_ray.x - p.x)) / d;
  float t = ((a.x - p.x) * (b.y - a.y) - (a.y - p.y) * (b.x - a.x)) / d;

  //checa condicionais para ver se houve uma interseção entre o vetor p end_ray e o vetor ab
  if (0 <= u && u <= 1 && 0 <= t && t <= 1) {
    //verifica se o raio atingiu um vertice, e define se o com uma rotação sentido horário o raio atingiria a aresta
    if (p.y == a.y) {
      if (a.y > b.y) {
        return 1;
      } else {
        return 0;
      }
    }
    if (p.y == b.y) {
      if (b.y > a.y) {
        return 1;
      } else {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

int inside(point p, point poly[], int n) {
  int hits = 0;

  for (int i = 0; i <= n - 2; i++) {
    int check_side = verify(p, poly[i], poly[i + 1]);

    if (check_side == 2) { // se o ponto esta em cima de qualquer aresta retorna 1
      return 1;
    }
    if (check_side == 1) {
      hits += 1; //Soma quantidade de interseções entre o raio e as arestas
    }
  }
  int last_side = verify(p, poly[n - 1], poly[0]);
  if (last_side == 2) {
    return 1;
  }
  if (last_side == 1) {
    hits += 1;
  }
  //verifica se for par está fora do polygono caso contrario esta dentro
  if (hits % 2 == 0) {
    return 0;
  } else {
    return 1;
  }
}
