<html>
	<head>
		<title>Pozetto's.NET</title>
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
		
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml();
	
	$_SESSION['arregloParametros'] = array(	"con_servidor" => "localhost",
																					"con_usuario" => "root",
																					"con_password" => "root",
																					"con_nombre_bd" => "pozettos");

  /* TITULO CON LA FECHA DEL DIA */
  $html->tag("table",array("class"=>"tbl_titulo tabla_centrada borde_azul"));
    $html->tag("tr");
      $html->tag("td", array("class"=>"alineacion_centro"));
        $html->tag("label");
          $html->printText("Pozetto's.Net");
        $html->end("label");
      $html->end("td");
      
      $html->tag("td", array("class"=>"ancho_40"));
        $html->tag("input", array("title"=>"Contabilidad", "type"=>"image", "src"=>"../imagenes/modulo_contabilidad.png", "value"=>date("Y-m-d"), "id"=>"con_fecha"), true);
      $html->end("td");
      
      $html->tag("td", array("class"=>"ancho_40"));
        $html->tag("input", array("title"=>"Deudores morosos", "type"=>"image", "src"=>"../imagenes/modulo_deuda.jpg", "onclick"=>"mostrarModulo('deuda');"), true);
      $html->end("td");
      
      $html->tag("td", array("class"=>"ancho_40"));
        $html->tag("input", array("title"=>"Estadisticas del negocio", "type"=>"image", "src"=>"../imagenes/reporte.jpg", "onclick"=>"mostrarModulo('estadistica');"), true);
      $html->end("td");
      
      $html->tag("td", array("class"=>"ancho_40"));
        $html->tag("input", array("title"=>"Clientes Fieles", "type"=>"image", "src"=>"../imagenes/add_user.png", "onclick"=>"mostrarModulo('cliente');"), true);
      $html->end("td");
    $html->end("tr");
  $html->end("table");

  //DIV CUERPO
  $html->tag("div", array("id"=>"div_cuerpo"));
    if(isset($_POST['modulo']))
      $_SESSION['modulo'] = $_POST['modulo'];
    else if(!isset($_SESSION['modulo']))
      $_SESSION['modulo'] = "panel";
    require_once("../modulo_".$_SESSION['modulo']."/fm_".$_SESSION['modulo'].".php");
  $html->end("div");
?>
	</body>
</html>