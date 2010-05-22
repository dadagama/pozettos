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

class GeneradorHtml
{
	/**
	 * Función encargada de imprimir el texto en la página normalizando su
	 * codificación y caracteres especiales.
	 * @param	$texto	cadena de texto a imprimir.
	 */
	function printText($texto)
	{
		echo stripslashes($texto);
	}
	
	/**
	 * Función que retorna un texto normalizando su codificación y
	 * caracteres especiales.
	 * @param	$texto	cadena de texto a normalizar.
	 * @return	string	cadena de texto normalizada.
	 */
	function getText($texto)
	{
		return stripslashes($texto);
	}

	/**
	 * Función que construye el inicio de una etiqueta html y la imprime.<br/>
	 * Cumple con el estandar xhtml.
	 * @param	$tag cadena con el tipo de etiqueta a imprimir.
	 * @param	$arrayAtributosAsociativos arreglo con los atributos de la etiqueta
	 * @param	$tag_una_linea	booleano que indica si es una etiqueta que se cierra
	 *												en la misma linea < ...  />.
	 * @return	string	Dato sintético generado. Su valor es uno de los 
	 * 					registros contenidos en la tabla.
	 */
	function tag($tag, $arrayAtributosAsociativos="", $tag_una_linea=false, $retornar=false)
	{
		$atributosAsociativos = "";
		$atributos = "";
		$fin_tag = "";
		if($arrayAtributosAsociativos)
			foreach($arrayAtributosAsociativos as $tipo => $valor)
				$atributosAsociativos .= "$tipo=\"$valor\"";
		if($tag_una_linea)
			$fin_tag = "/";
		if($retornar)
			return "<".stripslashes($tag)." ".stripslashes($atributosAsociativos)." $fin_tag>";
		else 
			echo "<".stripslashes($tag)." ".stripslashes($atributosAsociativos)." $fin_tag>";
	}

	/**
	 * Función que imprime una cantidad de saltos de linea html.<br/>
	 * Cumple con el estandar xhtml.
	 * @param	$num_saltos	cantidad de saltos a imprimir.
	 */	
	function br($num_saltos = 1)
	{
		for($x = 0; $x < $num_saltos; $x++)
			echo "<br/>";
	}

	/**
	 * Función que imprime una cantidad de espacios html.
	 * @param	$num_espacios	cantidad de espacios a imprimir.
	 */	
	function espacios($num_espacios = 1)
	{
		for($x = 0; $x < $num_espacios; $x++)
			echo "&nbsp;";
	}
	
	/**
	 * Función que construye el final de una etiqueta html y la imprime.<br/>
	 * Cumple con el estandar xhtml.
	 * @param	$tipo	cadena con el tipo de etiqueta a cerrar.
	 */	
	function end($tipo, $retornar=false) 
	{
		if($retornar)
			return "</$tipo>";
		else 
			echo "</$tipo>";
	}
	
	/**
	 * Función auxiliar que carga el archivo javascript del módulo.
	 * @param	$modulo	nombre del módulo y al mismo tiempo del archivo javascript.
	 */	
	function cargarModuloJS($modulo)
	{
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../modulo_$modulo/$modulo.js"));
		$this->end("script");
	}
	
	/**
	 * Función auxiliar que carga un archivo javascript.
	 * @param	$ruta_archivo	ruta del archivo javascript.
	 */	
	function cargarHerramientaJS($ruta_archivo)
	{
		$this->tag("script", array("type"=>"text/javascript", "src"=>"$ruta_archivo.js"));
		$this->end("script");
	}
	
	/**
	 * Función auxiliar que imprime una etiqueta SELECT de html.
	 * @param	$conexion	referencia de un objeto conexión de BD donde se consultará
											los valores del select.
	 * @param	$valor	cadena con el nombre del campo de la tabla que tiene los
										valores VALUE para las opciones del select. si se pasa
										vacio, se toma el TEXTO como VALUE
	 * @param	$texto	cadena con el nombre del campo de la tabla que tiene el
										TEXTO a mostrar en las opciones del select.
	 * @param	$nombre_tabla	cadena con el FROM de la consulta sql a realizar.
	 * @param	$condiciones	cadena con el WHERE de la consulta sql a realizar.
	 * @param	$valor_seleccionado	cadena con el VALUE seleccionado del select.
	 * @param	$arreglo_atributos_asociativos	arreglo con los atributos de la 
																						etiqueta.
	 * @param	$primera_opcion	cadena con el texto de la primera opción del select.
	 * @param	$finalizar_select	bandera que indica si la etiqueta select debe 
															cerrarse.
	 */	
	function printSelect(&$conexion = "", $valor = "", $texto, $nombre_tabla, $condiciones = "", $valor_seleccionado = "", $arreglo_atributos_asociativos = "", $primera_opcion = "", $finalizar_select = true)
	{
		$this->tag("select", $arreglo_atributos_asociativos);
		if($primera_opcion)
		{
			$this->tag("option", array("value"=>""));
				$this->printText($primera_opcion);
			$this->end("option");
		}
		if(!$valor)
			$valor = $texto;
		if($conexion)
		{
			$sql = "SELECT $valor, $texto
							FROM $nombre_tabla";
			if($condiciones)
				$sql .= " WHERE $condiciones";
			$conexion->ejecutarSQL($sql);
			$datos_opcion = array();
			while($datos_opcion = $conexion->obtenerFilaComoArregloAsociativo())
			{
				$seleccionado = "";
				if($datos_opcion[$valor] == $valor_seleccionado)
					$seleccionado = "selected";				
					
				$this->tag("option", array("value"=>$datos_opcion[$valor], $seleccionado=>$seleccionado));
					$this->printText($datos_opcion[$texto]);
				$this->end("option");
			}
		}
		if($finalizar_select)
			$this->end("select");
	}
	
	/**
	 * Función auxiliar que imprime un arreglo como opciones de un select html.
	 * @param	$arreglo_valores	arreglo con los valores a imprimir. puede ser un
															arreglo asociativo o normal.
	 * @param	$valor_seleccionado	cadena con el VALUE seleccionado del select.
	 * @param	$primera_opcion	cadena con el texto de la primera opción del select.
	 */	
	function arregloAOpciones($arreglo_valores = "", $valor_seleccionado = "", $primera_opcion = "")
	{
		if($primera_opcion)
		{
			$this->tag("option", array("value"=>""));
				$this->printText($primera_opcion);
			$this->end("option");
		}
		
		if($arreglo_valores)
		{
			foreach($arreglo_valores AS $pos => $texto)
			{
				$seleccionado = "";
				if($pos == $valor_seleccionado)
					$seleccionado = "selected";	
					
				$this->tag("option", array("value"=>$pos, $seleccionado=>$seleccionado));
					$this->printText($texto);
				$this->end("option");
			}
		}
	}
	
	function obtenerFechaTextual($fecha, $mostrar_anno = false, $mostrar_mes = true, $mes_extendido = true, $mostrar_dia = true)
	{
		//formato llegada: 2010-03-22
		$arreglo_fecha = explode("-", $fecha);
		$dia = $arreglo_fecha[2];
		$mes = $arreglo_fecha[1];
		$anno = $arreglo_fecha[0];
		$fecha_convertida = "";
		$arreglo_meses = array();
		if($mes_extendido)//extendido
			$arreglo_meses = array(	"Enero","Febrero","Marzo","Abril",
															"Mayo","Junio","Julio","Agosto",
															"Septiembre","Octubre","Novimebre","Diciembre");
		else // reducido
			$arreglo_meses = array(	"Ene","Feb","Mar","Abr",
															"May","Jun","Jul","Ago",
															"Sep","Oct","Nov","Dic");
		if($mostrar_mes)
			$fecha_convertida .= $arreglo_meses[$mes - 1];
		if($mostrar_dia)
			$fecha_convertida .= " ".$dia;
		if($mostrar_anno)
			$fecha_convertida .= " de ".$anno;
		return $fecha_convertida;	
	}

	function colocarPuntoMiles($numero)
	{
		$valor = $numero;
		if(strlen($valor)>9)
			$valor = substr($valor, 0, -9).".".substr($valor, -9);
		if(strlen($valor)>6)
			$valor = substr($valor, 0, -6).".".substr($valor, -6);
		if(strlen($valor)>3)
			$valor = substr($valor, 0, -3).".".substr($valor, -3);
		return $valor;
	}
}
?>
