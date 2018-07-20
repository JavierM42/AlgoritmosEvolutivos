import React, { Component } from 'react';
import Select from 'react-select';
import { Col, Row } from 'react-bootstrap';

export class Vertice extends Component {

  onCambioVertice(val) {
    this.props.cambiarVertice(this.props.idx, val.value);
  }

  render() {
    const opcionesVertice = [
      {value: 2, label: '2'},
      {value: 1, label: '1'},
      {value: 'X', label: 'X'},
      {value: 0, label: '0'},
    ];
    return (
      <Col xs={2} style={{padding: 3}}>
        <div className="col-xs-4"></div>
        <Select className="col-xs-4"
          clearable={false}
          name="arcilla-name"
          value={this.props.game.vertices[this.props.idx]}
          options={opcionesVertice}
          onChange={(val) => this.onCambioVertice(val)}
        />
        <div className="col-xs-4"></div>
      </Col>
    );
  }
}