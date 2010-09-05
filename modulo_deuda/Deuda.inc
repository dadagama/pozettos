<?php 
/*
 This file is part of Pozettos.

    Pozettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozettos.  If not, see <http://www.gnu.org/licenses/>.

*/


require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml2.inc");

class Deuda
{
	var $_conexionBD;	
	var $_conexionBDAux;
	var $_html;
	
	function __construct($parametrosConexion)
	{
		$this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
		$this->_conexionBD->conectar();
		$this->_conexionBDAux = new ConexionBDMySQL($parametrosConexion);
		$this->_conexionBDAux->conectar();
		$this->_html = new GeneradorHtml2();
	}
	
	function actualizarValor($hiv_id,$valor_nuevo,$nombre_campo)
	{
		if(!$valor_nuevo)
			$valor_nuevo = "";
		$sql = "UPDATE pozettos_historico_venta
						SET $nombre_campo = '".utf8_decode($valor_nuevo)."'
						WHERE hiv_id = '$hiv_id'";
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	
	function actualizarEstadoPago($id_fila, $hiv_chk_pago, $hiv_chk_gratis, $ultimo_clic)
	{
		$hiv_pago = 0;
		$hiv_es_tiempo_gratis = 0;
		if($ultimo_clic == "pago")
		{
			if($hiv_chk_pago == "true")
			{
				$hiv_es_tiempo_gratis = 0;
				$hiv_pago = 1;
				$set_adicional = ", hiv_deuda_real = 0";
			}
		}
		else if($ultimo_clic == "gratis")
		{
			if($hiv_chk_gratis == "true")
			{
				$hiv_es_tiempo_gratis = 1;
				$hiv_pago = 0;
				$set_adicional = ", hiv_deuda_real = 0";
			}
		}
	
		$sql = "UPDATE pozettos_historico_venta
						SET hiv_pago = '$hiv_pago',
						hiv_es_tiempo_gratis = '$hiv_es_tiempo_gratis'
						$set_adicional
						WHERE hiv_id = '$id_fila'";
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return $id_fila;
		else
			return false;
	}
	
	function actualizarHistorialDeudas()
	{
		$sql = "SELECT	hiv_id,
										hiv_fecha,
										hiv_cli_id,
										hiv_pago,
										hiv_es_tiempo_gratis,
										IF(hiv_ser_tipo = 'servicio', dus_texto, null) as dus_texto,
										hiv_total, 
										hiv_deuda_real,
										hiv_observacion, 
										ser_nombre,
										cli_nombre,
										cli_apellido
						FROM 	pozettos_historico_venta, pozettos_servicio, pozettos_cliente, pozettos_duracion_servicio
						WHERE hiv_ser_id = ser_id
						AND hiv_dus_minutos = dus_minutos
						AND hiv_cli_id = cli_id
						AND hiv_es_tiempo_gratis = 0
						AND hiv_pago = 0
						AND hiv_vigente = 1
						ORDER BY cli_nombre ASC, hiv_observacion ASC, hiv_fecha ASC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;
    
    $trs_historial = "";
		while($info_tupla_historico = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
//   		  $td_cli_id = $this->_html->tag("td", 
//                                         "class='alineacion_centro verdana letra_9' id='cli_id_".$info_tupla_historico['hiv_id']."' title='Código del cliente'", 
//                                         array("<label>".$info_tupla_historico['hiv_cli_id']."</label>"));
//         $td_cli_nombre = $this->_html->tag("td", 
//                                         "class='alineacion_izquierda verdana letra_9' title='Cliente que debe'", 
//                                         array("<label>".utf8_encode($info_tupla_historico['cli_nombre']." ".$info_tupla_historico['cli_apellido'])."</label>"));
        $td_fecha = $this->_html->tag("td", 
                                        "class='alineacion_centro verdana letra_9' title='Fecha de la deuda'", 
                                        array("<label>".$this->_html->obtenerFechaTextual($info_tupla_historico['hiv_fecha'],false,true,false,true)."</label>"));
        $td_servicio = $this->_html->tag("td", 
                                        "class='alineacion_izquierda verdana letra_9' title='Servicio prestado'", 
                                        array("<label>".utf8_encode($info_tupla_historico['ser_nombre'])."</label>"));
        $td_duracion = $this->_html->tag("td", 
                                        "class='alineacion_centro verdana letra_9' title='Duración del servicio prestado'", 
                                        array("<label>".utf8_encode($info_tupla_historico['dus_texto'])."</label>"));
        $td_total = $this->_html->tag("td", 
                                        "class='alineacion_derecha verdana letra_9' title='Total a pagar por el servicio' id='hiv_total_".$info_tupla_historico['hiv_id']."'", 
                                        array("<label>".utf8_encode($info_tupla_historico['hiv_total'])."</label>"));
        
        $label_deuda_real = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_deuda_real']));
        $td_deuda_real = $this->_html->tag("td", "class='alineacion_derecha verdana letra_9 cursor_cruz' title='Lo que debe realmente del valor total' id='hiv_deuda_real_".$info_tupla_historico['hiv_id']."' onclick=\"editableDeudaReal('hiv_deuda_real_".$info_tupla_historico['hiv_id']."',true);\"", array($label_deuda_real));

        
        $checked_pago = $checked_gratis = $clase_celda_gratis = "";
  			$clase_celda_pago = "celda_debe";
  			if($info_tupla_historico['hiv_pago'])
  			{
  				$checked_pago = "checked='checked'";
  				$clase_celda_pago = "celda_pago";
  			}
//   			else if($info_tupla_historico['hiv_es_tiempo_gratis'])
//   			{
//   				$clase_celda_pago = "";
//           $checked_gratis = "checked='checked'";
//   				$clase_celda_gratis = "celda_pago";
//   		  }
  		  $input_pago = $this->_html->tag("input", "$checked_pago type='checkbox' id='hiv_chk_pago_".$info_tupla_historico['hiv_id']."' onchange=\"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'pago');\"", "", true);
        $td_pago = $this->_html->tag("td", 
                                      "class='alineacion_centro $clase_celda_pago' title='Ya pagó el total del servicio'", 
                                      array($input_pago));
//   		  $input_gratis = $this->_html->tag("input", "$checked_gratis type='checkbox' id='hiv_chk_gratis_".$info_tupla_historico['hiv_id']."' onchange=\"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'gratis');\"", "", true);
//         $td_gratis = $this->_html->tag("td", 
//                                       "class='alineacion_centro $clase_celda_gratis' title='No se cobra porque es gratis'", 
//                                       array($input_gratis));
                                      
        $td_observacion = $this->_html->tag("td", 
                                            "class='alineacion_izquierda verdana letra_9 cursor_cruz' title='Información adicional' id='hiv_observacion_".$info_tupla_historico['hiv_id']."' onclick=\"editableObservacion('hiv_observacion_".$info_tupla_historico['hiv_id']."',true);\"", 
                                            array("<label>".utf8_encode($info_tupla_historico['hiv_observacion'])."</label>"));

  		  $input_sumar = $this->_html->tag("input", "type='checkbox' id='hiv_chk_sumar_".$info_tupla_historico['hiv_id']."' onchange=\"actualizarCalculadora(".$info_tupla_historico['hiv_id'].");\"", "", true);
        $td_sumar = $this->_html->tag("td", 
                                      "class='alineacion_centro title='Sumar en la calculadora'", 
                                      array($input_sumar));
		    
		  $trs_historial .= $this->_html->tag("tr", 
                                          "id='hiv_fila_".$info_tupla_historico['hiv_id']."' name='fila_historico'", 
                                          array(/*$td_cli_id,$td_cli_nombre,*/
                                                $td_fecha,$td_servicio,
                                                $td_duracion,$td_total,
                                                $td_deuda_real,$td_pago,
                                                /*$td_gratis,*/$td_observacion,
                                                $td_sumar));				
// 			$this->_html->tag("td", array("id"=>"hiv_pago_".$info_tupla_historico['hiv_id'], "title"=>"Ya pago el total del servicio", "class"=>"alineacion_centro $clase_celda_pago"));
// 				$this->_html->tag("input", array($checked_pago=>$checked_pago, "type"=>"checkbox", "id"=>"hiv_chk_pago_".$info_tupla_historico['hiv_id'], "onchange"=>"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'pago');"));
// 			$this->_html->end("td");
			$contador++;
		}
		return $trs_historial;
	}
}
?>