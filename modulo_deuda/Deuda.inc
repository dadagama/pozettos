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
	var $_html;
	
	function __construct($parametrosConexion)
	{
		$this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
		$this->_conexionBD->conectar();
		$this->_html = new GeneradorHtml();
	}

	function actualizarListaClientes($info_cliente)
	{
		$sql = "SELECT cli_id, CONCAT(cli_id, ' - ', cli_nombre, \" \", cli_apellido) as cli_nombre
						FROM pozettos_cliente
						WHERE cli_id like '$info_cliente'
						OR cli_nombre like '%$info_cliente%'
						OR cli_apellido like '%$info_cliente%'
						OR cli_id = 1
						ORDER BY cli_id ASC";

		$this->_conexionBD->ejecutarSQL($sql);
		
		$opciones_select = "";
		while($info_cliente = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$seleccionado = "";
			$opciones_select .= "<option value='".$info_cliente['cli_id']."' $seleccionado='$seleccionado'>".$info_cliente['cli_nombre']."</option>";
		}
		
		return $opciones_select;
	}
	
	function actualizarHistoricoProductos($cli_id)
	{
		$sql = "SELECT	vep_id,
										date_format(vep_fecha_venta, '%Y-%m-%d') as vep_fecha_venta,
										pro_nombre,
										date_format(vep_fecha_venta, '%l:%i%p') as vep_hora_venta,
										vep_total, 
										vep_observacion
										
						FROM 	pozettos_venta_producto, pozettos_producto
						WHERE vep_pro_id = pro_id
						AND vep_cli_id = '$cli_id'
						AND vep_pago = FALSE
						ORDER BY vep_fecha_venta DESC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;
		if($this->_conexionBD->obtenerNumeroFilas())
		{
			while($info_tupla_historico_producto = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
			{
				$fondo_default = "";
				if($contador % 2 == 0)
					$fondo_default = "fila_historial_par";
				else
					$fondo_default = "fila_historial_impar";
				
				$this->_html->tag("tr", array("class"=>$fondo_default, "id"=>"vep_fila_".$info_tupla_historico_producto['vep_id'], "name"=>"vep_fila"));
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($this->_html->obtenerFechaTextual($info_tupla_historico_producto['vep_fecha_venta'], false, true, false, true));
						$this->_html->end("label");
					$this->_html->end("td");
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText(utf8_encode($info_tupla_historico_producto['pro_nombre']));
						$this->_html->end("label");
					$this->_html->end("td");

					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($info_tupla_historico_producto['vep_hora_venta']);
						$this->_html->end("label");
					$this->_html->end("td");

					$this->_html->tag("td", array("class"=>"alineacion_derecha celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($info_tupla_historico_producto['vep_total']);
						$this->_html->end("label");
					$this->_html->end("td");

					$this->_html->tag("td", array("class"=>"alineacion_centro"));
						$this->_html->tag("input", array("id"=>"vep_observacion_".$info_tupla_historico_producto['vep_id'], "type"=>"text", "class"=>"input_observacion_producto celda_producto", "value"=>utf8_encode($info_tupla_historico_producto['vep_observacion']), "onchange"=>"actualizarObservacion(13, ".$info_tupla_historico_producto['vep_id'].", 'vep');"), true);
					$this->_html->end("td");

					$this->_html->tag("td", array("class"=>"alineacion_centro"));
						$this->_html->tag("button", array("class"=>"", "onclick"=>"actualizarEstadoDeuda(".$info_tupla_historico_producto['vep_id'].", 1, 'vep');"));
							$this->_html->printText(utf8_encode("Pagó"));
						$this->_html->end("button");
					$this->_html->end("td");
				$this->_html->end("tr");
				$contador++;
			}
		}
		else
		{
			$this->_html->tag("tr", array("class"=>$fondo_default, "id"=>"vep_fila_".$info_tupla_historico_producto['vep_id'], "name"=>"vep_fila"));
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto", "colspan"=>"5"));
						$this->_html->tag("label");
							$this->_html->printText("No tiene deudas de productos");
						$this->_html->end("label");
					$this->_html->end("td");
				$this->_html->end("tr");
		}
	}
	
	function actualizarHistoricoServicios($cli_id)
	{
		$sql = "SELECT	ves_id,
										date_format(ves_fecha, '%Y-%m-%d') as ves_fecha_venta,
										ser_nombre,
										time_format(ves_hora, '%l:%i%p') as ves_hora,
										ves_duracion,
										ves_total, 
										ves_observacion
						FROM 	pozettos_venta_servicio, pozettos_servicio
						WHERE ves_ser_id = ser_id
						AND ves_cli_id = '$cli_id'
						AND ves_pago = FALSE
						ORDER BY ves_fecha_venta DESC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;
		if($this->_conexionBD->obtenerNumeroFilas())
		{
			while($info_tupla_historico_producto = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
			{
				$fondo_default = "";
				if($contador % 2 == 0)
					$fondo_default = "fila_historial_par";
				else
					$fondo_default = "fila_historial_impar";
				
				$this->_html->tag("tr", array("class"=>$fondo_default, "id"=>"ves_fila_".$info_tupla_historico_producto['ves_id'], "name"=>"ves_fila"));
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($this->_html->obtenerFechaTextual($info_tupla_historico_producto['ves_fecha_venta'], false, true, false, true));
						$this->_html->end("label");
					$this->_html->end("td");
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText(utf8_encode($info_tupla_historico_producto['ser_nombre']));
						$this->_html->end("label");
					$this->_html->end("td");
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($info_tupla_historico_producto['ves_hora']);
						$this->_html->end("label");
					$this->_html->end("td");
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($info_tupla_historico_producto['ves_duracion']);
						$this->_html->end("label");
					$this->_html->end("td");
					
					$this->_html->tag("td", array("class"=>"alineacion_derecha celda_producto"));
						$this->_html->tag("label");
							$this->_html->printText($info_tupla_historico_producto['ves_total']);
						$this->_html->end("label");
					$this->_html->end("td");

					$this->_html->tag("td", array("class"=>"alineacion_centro"));
						$this->_html->tag("input", array("id"=>"ves_observacion_".$info_tupla_historico_producto['ves_id'], "type"=>"text", "class"=>"input_observacion_producto celda_producto", "value"=>utf8_encode($info_tupla_historico_producto['ves_observacion']), "onkeyup"=>"actualizarObservacion(event.keyCode, ".$info_tupla_historico_producto['ves_id'].", 'ves');", "onchange"=>"actualizarObservacion(13, ".$info_tupla_historico_producto['ves_id'].", 'ves');"), true);
					$this->_html->end("td");
					
					$this->_html->tag("td", array("class"=>"alineacion_centro"));
						$this->_html->tag("button", array("class"=>"", "onclick"=>"actualizarEstadoDeuda(".$info_tupla_historico_producto['ves_id'].", 1, 'ves');"));
							$this->_html->printText(utf8_encode("Pagó"));
						$this->_html->end("button");
					$this->_html->end("td");
				$this->_html->end("tr");
				$contador++;
			}
		}
		else
		{
			$this->_html->tag("tr", array("class"=>$fondo_default, "id"=>"vep_fila_".$info_tupla_historico_producto['vep_id'], "name"=>"vep_fila"));
					
					$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto", "colspan"=>"5"));
						$this->_html->tag("label");
							$this->_html->printText("No tiene deudas de servicios");
						$this->_html->end("label");
					$this->_html->end("td");
				$this->_html->end("tr");
		}
	}
	
	function actualizarEstadoDeuda($prefijo, $id_fila, $estado)
	{
		$tabla = "";
		if($prefijo == "vep")
			$tabla = "pozettos_venta_producto";
		else if($prefijo == "ves")
			$tabla = "pozettos_venta_servicio";
		$reiniciar_color = "";
		//FUNCIONALIDAD COMENTADA SIN APROBAR:
		//Quitar el color de la fila cuando se pague la deuda
		//if($estado)
			//$reiniciar_color = ", ".$prefijo."_color_fila = null";
		$sql = "UPDATE $tabla
						SET ".$prefijo."_pago = '$estado'
						$reiniciar_color
						WHERE ".$prefijo."_id = '$id_fila'";
		$this->_conexionBD->ejecutarSQL($sql);
		return $prefijo;
	}
	
	function actualizarObservacion($prefijo, $id_fila, $observacion)
	{
		$tabla = "";
		if($prefijo == "vep")
			$tabla = "pozettos_venta_producto";
		else if($prefijo == "ves")
			$tabla = "pozettos_venta_servicio";
			
		$sql = "UPDATE $tabla
						SET ".$prefijo."_observacion = '$observacion'
						WHERE ".$prefijo."_id = '$id_fila'";
		$this->_conexionBD->ejecutarSQL($sql);
		echo $sql;
	}
}
?>
