#!/bin/bash

#Um exemplo de como rodar o programa para uma rede chamada 'teste.net'

#Para gerar o dendrogramo
./BetweennessCentrality teste.net d filename 

#Para gerar a matriz de cores na iteracao 0 (sem remover nenhuma aresta)
./BetweennessCentrality teste.net c filename 0 
./BetweennessCentrality teste.net c filename 0 

#Para gerar a matriz de cores na iteracao 2
./BetweennessCentrality teste.net c filename 2
./BetweennessCentrality teste.net c filename 2

#Para gerar a matriz de cores na iteracao 3
./BetweennessCentrality teste.net c filename 3 
./BetweennessCentrality teste.net c filename 3 

