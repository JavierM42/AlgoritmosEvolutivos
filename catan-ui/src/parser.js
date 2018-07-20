import React, { Component } from 'react';

export class Parser extends Component {
  render() {
    console.log(this.props.game.aristas);
    return (
      <div style={{textAlign: 'left', padding : 10}}>
        terrenos:
        {
          this.props.game.terrenos.map(
            (t,i) =>
              " "+t
          )
        }
        <br/>
        numeros:
        {
          this.props.game.numeros.map(
            (n,i) =>
              " "+n
          )
        }
        <br/>
        puertos: rellenar puertos manualmente!
        <br/>
        construccionesOponentes:
        {
          this.props.game.vertices.map(
            (v,i) =>
              v=='X' ? " 1":" 0"
          )
        }
        <br/>
        aristasOcupadas:
        {
          this.props.game.aristas.map(
            (destinos,i) =>
              destinos.map(
                (destino, j) =>
                  destino=="O" ? " "+i+","+j : null
              )
          )
        }
        <br/>
        construcciones:
        {
          this.props.game.vertices.map(
            (v,i) =>
              v=='X' ? " 0":" "+v
          )
        }
        <br/>
        caminos:
        {
          this.props.game.aristas.map(
            (destinos,i) =>
              destinos.map(
                (destino, j) =>
                  destino=="Y" ? " "+i+","+j : null
              )
          )
        }
        <br/>
        reserva: T:0 A:0 M:0 P:0 O:0 puntos:0
        <br/>
        *
      </div>
    );
  }
}