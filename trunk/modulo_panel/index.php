<?php
	function showLogin() 
	{
			header('WWW-Authenticate: Basic realm="Demo System"');
			header('HTTP/1.0 401 Unauthorized');
			echo "Usted no tiene permisos para ingresar.\n";
			exit;
	}

	$username = $_SERVER['PHP_AUTH_USER'];
	$userpass = $_SERVER['PHP_AUTH_PW'];
	if (!($username == "123" && $userpass == "123"))
			showLogin();

	session_start();
?>
<html>
	<head>
		<title>Pozetto's.NET</title>
		<link rel="icon" type="image/gif" href="../imagenes/animated_favicon1.gif"/>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
		<link rel="stylesheet" type="text/css" href="../estilos/general.css"/>
    <link rel="stylesheet" type="text/css" href="../estilos/redmond/ui.all.css" />
		<link rel="stylesheet" type="text/css" href="../estilos/redmond/ui.datepicker.css" />
    <script src="../herramientas/jquery-1.4.2.min.js" type="text/javascript"></script>
		<script src="../herramientas/general.js" type="text/javascript"></script>
		<script src="../herramientas/validacion.js" type="text/javascript"></script>
		<script src="../herramientas/ui.core.js" type="text/javascript"></script>
		<script src="../herramientas/ui.datepicker.js" type="text/javascript"></script>
		<script src="../herramientas/jquery.tablesorter.min.js" type="text/javascript"></script>
		<script src="../herramientas/jquery.vreboton.ColorPicker.js" type="text/javascript"></script>
	</head>
	<body>
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


		
	require_once("../herramientas/GeneradorHtml2.inc");
	$html = new GeneradorHtml2();
	
	$_SESSION['arregloParametros'] = array(	"con_servidor" => "localhost",
																					"con_usuario" => "root",
																					"con_password" => "root",
																					"con_nombre_bd" => "pozettos");

  //td's titulo
  $td_titulo = $html->tag("td", "class='alineacion_centro'", array("<label>Pozetto's.Net</label>"));
  $input_contabilidad = $html->tag("input", "title='Contabilidad' type='image' src='../imagenes/modulo_contabilidad.png' value='".date("Y-m-d")."' id='con_fecha'", "", true);
  $td_contabilidad = $html->tag("td", "class='ancho_40'", array($input_contabilidad));
  $input_deudores = $html->tag("input", "title='Deudores morosos' type='image' src='../imagenes/modulo_deuda.jpg' onclick=\"mostrarModulo('deuda');\"", "", true);
  $td_deudores = $html->tag("td", "class='ancho_40'", array($input_deudores));
  $input_estadistica = $html->tag("input", "title='Estadisticas del negocio' type='image' src='../imagenes/reporte.jpg' onclick=\"mostrarModulo('estadistica');\"", "", true);
  $td_estadistica = $html->tag("td", "class='ancho_40'", array($input_estadistica));
  $input_clientes = $html->tag("input", "title='Clientes Fieles' type='image' src='../imagenes/home.png' onclick=\"mostrarModulo('cliente');\"", "", true);
  $td_clientes = $html->tag("td", "class='ancho_40'", array($input_clientes));
  //tr titulo
  $tr_titulo = $html->tag("tr", "", array($td_titulo,$td_contabilidad,$td_deudores,$td_estadistica,$td_clientes));
  //table titulo
  echo $html->tag("table", "class='tbl_titulo tabla_centrada borde_azul'", array($tr_titulo));

  //DIV CUERPO
  if(isset($_POST['modulo']))
    $_SESSION['modulo'] = $_POST['modulo'];
  else if(!isset($_SESSION['modulo']))
    $_SESSION['modulo'] = "panel";
  require_once("../modulo_".$_SESSION['modulo']."/fm_".$_SESSION['modulo'].".php");
  //la variable $contenido_modulo debe estar en todos los fm_
  //es un arreglo que contiene los bloques de cada interfaz que se mostraran
  echo $html->tag("div", "id='div_cuerpo'", array($contenido_modulo));
?>
	</body>
</html>