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
require_once("../herramientas/GeneradorHtml.inc");

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
		$this->_html = new GeneradorHtml();
	}
	
	function actualizarValor($hiv_id,$valor_nuevo,$nombre_campo)
	{
		if(!$valor_nuevo)
			$valor_nuevo = "0";
		$sql = "UPDATE pozettos_historico_venta
						SET $nombre_campo = '$valor_nuevo'
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
			}
		}
		else if($ultimo_clic == "gratis")
		{
			if($hiv_chk_gratis == "true")
			{
				$hiv_es_tiempo_gratis = 1;
				$hiv_pago = 0;
			}
		}
	
		$reiniciar_color = "";
		$sql = "UPDATE pozettos_historico_venta
						SET hiv_pago = '$hiv_pago',
						hiv_es_tiempo_gratis = '$hiv_es_tiempo_gratis'
						$reiniciar_color
						WHERE hiv_id = '$id_fila'";
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
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
										hiv_observacion, 
										ser_nombre,
										cli_nombre
						FROM 	pozettos_historico_venta, pozettos_servicio, pozettos_cliente, pozettos_duracion_servicio
						WHERE hiv_ser_id = ser_id
						AND hiv_dus_minutos = dus_minutos
						AND hiv_cli_id = cli_id
						AND hiv_es_tiempo_gratis = 0
						AND hiv_pago = 0
						ORDER BY cli_nombre ASC, hiv_fecha ASC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;

		while($info_tupla_historico = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$fondo_default = "";
			if($contador % 2 == 0)
				$fondo_default = "fila_historial_par";
			else
				$fondo_default = "fila_historial_impar";
			
			$this->_html->tag("tr", array("style"=>$hiv_color_fila, "class"=>$fondo_default, "id"=>"hiv_fila_".$info_tupla_historico['hiv_id'], "name"=>"fila_historico"));
				
				$this->_html->tag("td", array("class"=>"alineacion_izquierda"));
					$this->_html->tag("label", array("id"=>"cli_fila_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9", "title"=>"Cliente que debe"));
							$this->_html->printText(utf8_encode($info_tupla_historico['cli_nombre']));
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("class"=>"verdana letra_9", "title"=>"Fecha de la deuda"));
						$this->_html->printText(utf8_encode($info_tupla_historico['hiv_fecha']));
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_izquierda"));
					$this->_html->tag("label", array("class"=>"verdana letra_9", "title"=>"Servicio prestado"));
						$this->_html->printText(utf8_encode($info_tupla_historico['ser_nombre']));
					$this->_html->end("label");
				$this->_html->end("td");
								
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("title"=>"Duracion del servicio prestado", "id"=>"hiv_dus_minutos_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9"));
						$this->_html->printText($info_tupla_historico['dus_texto']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_derecha"));
					$this->_html->tag("label", array("title"=>"Total a pagar por el servicio", "id"=>"hiv_total_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9"));
						$this->_html->printText($info_tupla_historico['hiv_total']);
					$this->_html->end("label");
				$this->_html->end("td");

				$checked_pago = "";
				$clase_celda_pago = "celda_debe";
				
				if($info_tupla_historico['hiv_pago'])
				{
					$checked_pago = "checked";
					$clase_celda_pago = "celda_pago";
				}
				else if($info_tupla_historico['hiv_es_tiempo_gratis'])
					$clase_celda_pago = "";
				
				$this->_html->tag("td", array("id"=>"hiv_pago_".$info_tupla_historico['hiv_id'], "class"=>"alineacion_centro $clase_celda_pago"));
					$this->_html->tag("input", array("title"=>"Ya pago el total del servicio", $checked_pago=>$checked_pago, "type"=>"checkbox", "id"=>"hiv_chk_pago_".$info_tupla_historico['hiv_id'], "onchange"=>"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'pago');"));
				$this->_html->end("td");
				
				$checked_gratis = "";
				$clase_celda_gratis = "";
				if($info_tupla_historico['hiv_es_tiempo_gratis'])
				{
					$checked_gratis = "checked";
					$clase_celda_gratis = "celda_pago";
				}
				
				$this->_html->tag("td", array("id"=>"hiv_pago_".$info_tupla_historico['hiv_id'], "class"=>"alineacion_centro $clase_celda_gratis"));
					$this->_html->tag("input", array("title"=>"No se cobra porque es gratis", $checked_gratis=>$checked_gratis, "type"=>"checkbox", "id"=>"hiv_chk_gratis_".$info_tupla_historico['hiv_id'], "onchange"=>"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'gratis');"));
				$this->_html->end("td");
					
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("title"=>"Nota adicional si se necesita", "id"=>"hiv_observacion_".$info_tupla_historico['hiv_id'], "type"=>"text", "class"=>"ancho_90p verdana letra_9", "value"=>utf8_encode($info_tupla_historico['hiv_observacion']), "onchange"=>"actualizarValor('hiv_observacion_".$info_tupla_historico['hiv_id']."','hiv_observacion', 13);", "onkeypress"=>"actualizarValor('hiv_observacion_".$info_tupla_historico['hiv_id']."','hiv_observacion', event.keyCode);"), true);
				$this->_html->end("td");
			$this->_html->end("tr");
			$contador++;
		}
	}
}
?>
