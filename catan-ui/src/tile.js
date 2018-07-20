import React, { Component } from 'react';
import Select from 'react-select';
import { Col, Row } from 'react-bootstrap';

export class Tile extends Component {

  onCambioTerreno(val) {
    this.props.cambiarTerreno(this.props.idx, val.value);
  }

  onCambioNumero(val) {
    this.props.cambiarNumero(this.props.idx, val.value);
  }

  render() {
    const opcionesTerrenos = [
      {value: 'T', label: 'Trigo'},
      {value: 'A', label: 'Arcilla'},
      {value: 'M', label: 'Madera'},
      {value: 'O', label: 'Oveja'},
      {value: 'P', label: 'Piedra'},
      {value: 'D', label: 'Desierto'}
    ];
    const opcionesNumeros = [
      {value: 2, label: '2'},
      {value: 3, label: '3'},
      {value: 4, label: '4'},
      {value: 5, label: '5'},
      {value: 6, label: '6'},
      {value: 8, label: '8'},
      {value: 9, label: '9'},
      {value: 10, label: '10'},
      {value: 11, label: '11'},
      {value: 12, label: '12'},
      {value: -1, label: 'Ninguno'}
    ];
    return (
      <Col xs={11} style={{padding: 3}}>
        <Select
          clearable={false}
          name="arcilla-name"
          value={this.props.game.terrenos[this.props.idx]}
          options={opcionesTerrenos}
          onChange={(val) => this.onCambioTerreno(val)}
        />
         <Select
          clearable={false}
          name="numeros-name"
          value={this.props.game.numeros[this.props.idx]}
          options={opcionesNumeros}
          onChange={(val) => this.onCambioNumero(val)}
        />
      </Col>
    );
  }
}