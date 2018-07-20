import React, { Component } from 'react';
import Select from 'react-select';
import { Col, Row } from 'react-bootstrap';

export class Arista extends Component {
  constructor(props) {
    super(props);
    this.dibujar = this.dibujar.bind(this);
    this.onCambioArista = this.onCambioArista.bind(this);
  }

  onCambioArista() {
    this.props.cambiarArista(this.props.origen, this.props.destino);
  }

  dibujar(val) {
    

  }

  render() {
    var color = "#dddddd";
    if (this.props.game.aristas[this.props.origen][this.props.destino]=="Y") {
      color = "#00ff00";
    }
    if (this.props.game.aristas[this.props.origen][this.props.destino]=="O") {
      color = "#ff0000";
    }

    return (
      <Col xs={1} style={{padding: 3}}>
        <div onClick={() => this.onCambioArista(this.props.origen, this.props.destino)}
          style={{backgroundColor: color}}
        >_</div>
      </Col>
    );
  }
}