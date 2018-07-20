import React, { Component } from 'react';
import './App.css';
import { Tablero } from './tablero';
import { Parser } from './parser';
import 'react-select/dist/react-select.css';
import { Grid, Col, Row } from 'react-bootstrap';


class App extends Component {
  constructor(props) {
    super(props);
    var x = new Array(54);
    for(var i=0; i<54; i++) {
      x[i] = new Array(54).fill(null);
    }
    this.state = {
      game: {
        terrenos: ["T", "A", "A", "D", "M", "M", "O", "P", "M", "P", "O", "A", "T", "D", "T", "O", "M", "T", "O"],
        numeros : [6, 8, 12, -1, 6, 9, 2, 11, 2, 3, 4, 5, 6, 9, 8, 3, 10, 11, 5],
        vertices : new Array(54).fill(0),
        aristas : x
      }
    };
    
    this.cambiarTerreno = this.cambiarTerreno.bind(this);
    this.cambiarNumero = this.cambiarNumero.bind(this);
    this.cambiarVertice = this.cambiarVertice.bind(this);
    this.cambiarArista = this.cambiarArista.bind(this);
  }

  cambiarTerreno(idx,val) {
    var g = this.state.game;
    g.terrenos[idx] = val;
    this.setState({game : g});
  }

  cambiarNumero(idx,val) {
    var g = this.state.game;
    g.numeros[idx] = val;
    this.setState({game : g});
  }

  cambiarVertice(idx,val) {
    var g = this.state.game;
    g.vertices[idx] = val;
    this.setState({game : g});
  }

  cambiarArista(origen, destino) {
    console.log(origen);
    var g = this.state.game;
    var next = "Y";
    if(g.aristas[origen][destino]=="Y") {
      next = "O";
    }
    if(g.aristas[origen][destino]=="O") {
      next = null;
    }
    g.aristas[origen][destino] = next;
    this.setState({game: g});
  }

  render() {
    return (
      <div className="App">
        <Tablero
          game={this.state.game}
          cambiarTerreno={(idx, val) => this.cambiarTerreno(idx, val)}
          cambiarNumero={(idx, val) => this.cambiarNumero(idx, val)}
          cambiarVertice={(idx, val) => this.cambiarVertice(idx, val)}
          cambiarArista={(origen, destino, val) => this.cambiarArista(origen, destino, val)}
        />
        <Parser game={this.state.game}/>
      </div>
    );
  }
}

export default App;
