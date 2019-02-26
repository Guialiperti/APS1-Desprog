#include <math.h>

#include "geometry.h"

int verify(point p, point a, point b) {

  //Verifica se os pontos a e b são iguais, caso sim retorna 0
  if(a.x - b.x == 0 && a.y - b.y == 0){
    if(p.y == a.y && p.x == a.x && p.y == b.y && p.x == b.x){
      return 2;
    }
    return 0;
  }

  //Checa se o ponto p esta no segmento AB
  int crossproduct = (p.y - a.y) * (b.x - a.x) - (p.x - a.x) * (b.y - a.y);
  int dotproduct = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
  int squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
  if(crossproduct == 0 && dotproduct >= 0 && dotproduct <= squaredlengthba){
    return 2;
  }
  //define o ponto de destino do raio 
  point end_ray;
  end_ray.y = p.y;
  end_ray.x = p.x + 2000;

  //checa se um raio disparado a direita colide com a aresta
	float d = (end_ray.x - p.x) * (b.y -a.y) - (end_ray.y - p.y) * (b.x - a.x); 
	float u = ((a.x - p.x) * (end_ray.y - p.y) - (a.y - p.y) * (end_ray.x - p.x)) / d;
	float t = ((a.x - p.x) * (b.y - a.y) - (a.y - p.y) * (b.x - a.x)) / d;

  //encontra o ponto de interseção (não é utilizado nesse momento)
  point hit;
  hit.x = a.x + ((b.x - a.x) * t);
  hit.y = a.y + ((b.y - a.y) * t);

  //checa condicionais para ver se houve uma interseção entre o vetor p end_ray e o vetor ab 
  if(0 <= u && u <= 1 && 0 <= t && t <= 1){
    if(p.y == a.y){
      if(a.y > b.y){
      return 1;
      }
    else{
      return 0;
    }
    }
    if(p.y == b.y){
      if(b.y > a.y){
        return 1;
      }
      else{
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

int inside(point p, point poly[], int n) {
  return 0;
}
