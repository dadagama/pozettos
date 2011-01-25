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

class Estadistica
{
  var $_conexionBD; 
  var $_conexionBDAux;
  var $_html;
  var $_resumen_general;
  var $_total_general;
  var $_deben_general;
  var $_total_venta_fullcarga;
  
  function __construct($parametrosConexion)
  {
    $this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBD->conectar();
    $this->_conexionBDAux = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBDAux->conectar();
    $this->_html = new GeneradorHtml2();
    $this->_resumen_general = array();
    $this->_total_general = 0;
    $this->_deben_general = 0;
    $this->_total_venta_fullcarga = 0;
  }
  
  function cargarCategorias()
  {
    $sql = "SELECT cat_id, cat_nombre
            FROM pozettos_categoria
            WHERE cat_id != 1
            AND cat_vigente = 1";
    $this->_conexionBD->ejecutarSQL($sql);
    $arreglo_tr_categorias = "";
    while($info_categoria = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
            $input_categoria = $this->_html->tag("input", "type='checkbox' name='".$info_categoria['cat_nombre']."' id='chk_".$info_categoria['cat_id']."' checked='checked'", "", true);
          $label_categoria = $this->_html->tag("label", "class='letra_azul verdana letra_9'", array($input_categoria,utf8_encode($info_categoria['cat_nombre'])));
        $td_categoria = $this->_html->tag("td", "", array($label_categoria));
      $tr_categorias .= $this->_html->tag("tr", "", array($td_categoria));
      $contador++;
    }
    return $this->_html->tag("table", "", array($tr_categorias));
  }
  
  function actualizarEstadisticas(&$arreglo_parametros)
  {
    switch($arreglo_parametros['opc_alcance'])
    {
      case "diario":
        $fecha = "hiv_fecha = '".$arreglo_parametros['opc_fecha']."'";
        break;
        
      case "mensual":
        $fecha = "hiv_fecha LIKE '".$arreglo_parametros['opc_anno']."-".$arreglo_parametros['opc_mes']."-__'";
        break;
        
      case "rango":
         $fecha = "hiv_fecha >= '".$arreglo_parametros['opc_fecha_inicial']."' AND hiv_fecha <= '".$arreglo_parametros['opc_fecha_final']."'";
        break;
    }
      $tablas_resumenes = "";  
      if($arreglo_parametros['Cabinas'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Cabinas");
      if($arreglo_parametros['Juegos'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Juegos");
      if($arreglo_parametros['Recargas'])
        if($arreglo_parametros['opc_alcance'] == "diario")
          $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Recargas", true, $arreglo_parametros['opc_fecha']);
        else
          $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Recargas");
      if($arreglo_parametros['Llamadas'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Llamadas");
      if($arreglo_parametros['Otros'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Otros");
      $tablas_resumenes = $this->_construirTablaResumenGeneral($arreglo_parametros)."".$tablas_resumenes;
      $tabla_resumen = $this->_html->tag("table", "class='tbl_resumen'", array($tablas_resumenes));
    $td_estadisticas = $this->_html->tag("td", "", array($tabla_resumen));
    return $this->_html->tag("tr", "", array($td_estadisticas));
  }
  
  function _construirTablaResumenGeneral(&$arreglo_parametros)
  {
        $th_categoria = $this->_html->tag("th", "class='ancho_140'", array("<label> RESUMEN </label>"));
        $th_total = $this->_html->tag("th", "class='ancho_70'", array("<label>Pagado</label>"));
        $th_deben = $this->_html->tag("th", "class='ancho_70'", array("<label>Deben</label>"));
      $tr_encabezado = $this->_html->tag("tr", "", array($th_categoria,$th_total,$th_deben));
    $thead_resumen = $this->_html->tag("thead", "", array($tr_encabezado));
    
    $totales = "";
    foreach ($this->_resumen_general  AS $fila)
      $totales .= $this->_html->tag("tr", "", array($fila));


      $td_total = $this->_html->tag("td", "class='celda_total'", array("<label>Total</label>"));
      $td_total_entrada = $this->_html->tag("td", "class='celda_total alineacion_derecha' colspan='1'", array("<label>".$this->_html->colocarPuntoMiles($this->_total_general)."</label>"));
      $td_total_deben = $this->_html->tag("td", "class='celda_total alineacion_derecha' colspan='1'", array("<label>".$this->_html->colocarPuntoMiles($this->_deben_general)."</label>"));
    $tr_total = $this->_html->tag("tr", "", array($td_total,$td_total_entrada,$td_total_deben));
    $totales .= $tr_total;

    //coloco plata que sale
    //y saldo base
    //y abonos de deudas viejas
    if($arreglo_parametros['opc_alcance'] == "diario")
    {
        $td_label_base = $this->_html->tag("td", "class='celda_subtotal'", array("<label>Base</label>"));
        $sql = "SELECT bas_saldo
                FROM pozettos_base_diaria
                WHERE bas_fecha = '".$arreglo_parametros['opc_fecha']."'
                AND bas_vigente = 1
                LIMIT 1";
        $this->_conexionBDAux->ejecutarSQL($sql);
        if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
          $total_base = $this->_conexionBDAux->obtenerFilaComoCadena();
        else
          $total_base = "0";
        $td_saldo_base = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_base)."</label>"));
      $tr_total_base = $this->_html->tag("tr", "", array($td_label_base,$td_saldo_base));
      $totales .= $tr_total_base;

        $td_label_abonos = $this->_html->tag("td", "class='celda_subtotal'", array("<label>Abonos deudas</label>"));
        $sql = "SELECT sav_saldo
                FROM pozettos_abono_deuda_vieja
                WHERE sav_fecha = '".$arreglo_parametros['opc_fecha']."'
                AND sav_vigente = 1
                LIMIT 1";
        $this->_conexionBDAux->ejecutarSQL($sql);
        if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
          $total_abono = $this->_conexionBDAux->obtenerFilaComoCadena();
        else
          $total_abono = "0";
        $td_abono = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_abono)."</label>"));
      $tr_total_abonos = $this->_html->tag("tr", "", array($td_label_abonos,$td_abono));
      $totales .= $tr_total_abonos;

        $td_label_egresos = $this->_html->tag("td", "class='celda_total_2'", array("<label>Plata que salió</label>"));
        $sql = "SELECT egd_saldo
                FROM pozettos_egreso_diario
                WHERE egd_fecha = '".$arreglo_parametros['opc_fecha']."'
                AND egd_vigente = 1
                LIMIT 1";
        $this->_conexionBDAux->ejecutarSQL($sql);
        if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
          $total_egreso = $this->_conexionBDAux->obtenerFilaComoCadena();
        else
          $total_egreso = "0";
        $td_saldo_egreso = $this->_html->tag("td", "class='celda_total_2 alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_egreso)."</label>"));
      $tr_total_egreso = $this->_html->tag("tr", "", array($td_label_egresos,$td_saldo_egreso));
      $totales .= $tr_total_egreso;

        $td_label_efectivo = $this->_html->tag("td", "class='celda_total'", array("<label>Efectivo Total</label>"));
        $td_saldo_efectivo = $this->_html->tag("td", "class='celda_total alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($this->_total_general + $total_base + $total_abono - $total_egreso)."</label>"));
      $tr_total_efectivo = $this->_html->tag("tr", "", array($td_label_efectivo,$td_saldo_efectivo));
      $totales .= $tr_total_efectivo;

    }
    
    $tbody_resumen = $this->_html->tag("tbody", "", array($totales));
    return $thead_resumen." ".$tbody_resumen;
  }
  
  function _construirTablaResumen($where_fecha, $cat_nombre, $mostrar_saldo_titan = false, $fecha = "")
  {
    $sql = "SELECT ser_nombre, ser_id
            FROM pozettos_servicio, pozettos_categoria, pozettos_categoria_servicios
            WHERE cas_ser_id = ser_id
            AND cas_cat_id = cat_id
            AND cat_nombre = '$cat_nombre'
            AND cat_vigente = 1
						AND cas_vigente = 1
						AND ser_vigente = 1
            ORDER BY ser_nombre ASC";
    $this->_conexionBD->ejecutarSQL($sql);
    
        $th_nombre_categoria = $this->_html->tag("th", "class='ancho_140'", array("<label>$cat_nombre</label>"));
        $th_pagado = $this->_html->tag("th", "class='ancho_70'", array("<label>Pagado</label>"));
        $th_deben = $this->_html->tag("th", "class='ancho_70'", array("<label>Deben</label>"));
//         $th_gratis = $this->_html->tag("th", "class='ancho_70'", array("<label>Gratis</label>"));
      $tr_encabezado = $this->_html->tag("tr", "", array($th_nombre_categoria,$th_pagado,$th_deben/*,$th_gratis*/));
    $thead_resumen = $this->_html->tag("thead", "", array($tr_encabezado));

    $total_pagado = 0;
    $total_deben = 0;
    $total_gratis = 0;
      
    $trs_servicios = "";
    while($info_cabina = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
        $td_nombre_servicio = $this->_html->tag("td", "class='alineacion_izquierda'", array("<label>".$info_cabina['ser_nombre']."</label>"));
        //se coloca (hiv_pago = 0 AND hiv_es_tiempo_gratis = 0 AND hiv_deuda_Real != 0 AND hiv_total != 0))
        //para que tenga en cuenta los abonos que hace el cliente a una deuda y se tengan en cuenta como
        //como plata pagada
        $sql = "SELECT SUM(IF(hiv_deuda_Real != 0, (hiv_total - hiv_deuda_Real), hiv_total))
                FROM pozettos_historico_venta
                WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND ( (hiv_pago = 1 AND hiv_es_tiempo_gratis = 0)
                            OR
                            (hiv_pago = 0 AND hiv_es_tiempo_gratis = 0 AND hiv_deuda_Real != 0 AND hiv_total != 0))
                      AND hiv_vigente = 1
                      AND $where_fecha";
        $this->_conexionBDAux->ejecutarSQL($sql);
        $total = (int)$this->_conexionBDAux->obtenerFilaComoCadena();
        $total_pagado += $total;
        $td_pago = $this->_html->tag("td", "class='alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));

        $sql = "SELECT SUM(IF(hiv_deuda_Real != 0, hiv_deuda_Real, hiv_total))
                FROM pozettos_historico_venta
                WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 0
                      AND hiv_es_tiempo_gratis = 0
                      AND hiv_vigente = 1
                      AND $where_fecha";
        $this->_conexionBDAux->ejecutarSQL($sql);
        $total = (int)$this->_conexionBDAux->obtenerFilaComoCadena();
        $total_deben += $total;
        $td_deben = $this->_html->tag("td", "class='alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));

//         $sql = "SELECT SUM(hiv_total)
//                 FROM pozettos_historico_venta
//                 WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
//                       AND hiv_pago = 0
//                       AND hiv_es_tiempo_gratis = 1
//                       AND hiv_vigente = 1
//                       AND $where_fecha";
//         $this->_conexionBDAux->ejecutarSQL($sql);
//         $total = (int)$this->_conexionBDAux->obtenerFilaComoCadena();
//         $total_gratis += $total;
//         $td_gratis = $this->_html->tag("td", "class='alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));
        
        
        if($info_cabina['ser_id'] == "10")//es recarga FULLCARGA
        {
          $this->_total_venta_fullcarga = $total_pagado + $total_deben/* + $total_gratis*/;
        }
        if($info_cabina['ser_id'] == "11")//es recarga TIGO
        {
          $this->_total_venta_tigo = $total_pagado + $total_deben/* + $total_gratis*/;
        }

      $trs_servicios .= $this->_html->tag("tr", "", array($td_nombre_servicio,$td_pago,$td_deben,$td_gratis));
    }
    //subtotales
      $td_subtotal = $this->_html->tag("td", "class='celda_subtotal'", array("<label>Subtotal</label>"));
      $td_total_pagado = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_pagado)."</label>"));
      $td_total_deben = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_deben)."</label>"));
//       $td_total_gratis = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_gratis)."</label>"));
    $tr_subtotal = $this->_html->tag("tr", "", array($td_subtotal,$td_total_pagado,$td_total_deben/*,$td_total_gratis*/));
    //totales
      $td_total = $this->_html->tag("td", "class='celda_total'", array("<label>Total $cat_nombre</label>"));
      $td_total_entrada = $this->_html->tag("td", "class='celda_total alineacion_centro' colspan='2'", array("<label>".$this->_html->colocarPuntoMiles($total_pagado + $total_deben)."</label>"));
    $tr_total = $this->_html->tag("tr", "", array($td_total,$td_total_entrada));

    //añado totales al arreglo de resumen general
    $td_label_total_general = $this->_html->tag("td", "class='celda_subtotal'", array("<label>$cat_nombre</label>"));
    $td_total_general = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha' colspan='1'", array("<label>".$this->_html->colocarPuntoMiles($total_pagado)."</label>"));
    $td_deben_general = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha' colspan='1'", array("<label>".$this->_html->colocarPuntoMiles($total_deben)."</label>"));
    $this->_resumen_general[] = $td_label_total_general."".$td_total_general."".$td_deben_general;
    $this->_total_general += $total_pagado;
    $this->_deben_general += $total_deben;

    $trs_titan = "";
    if($mostrar_saldo_titan)
    {
        $td_label_titan = $this->_html->tag("td", "class='celda_total_2'", array("<label>Saldo Inicial Titan</label>"));
        $sql = "SELECT sit_saldo
                FROM pozettos_saldo_inicial_titan
                WHERE sit_fecha = '$fecha'
                AND sit_vigente = 1
                LIMIT 1";
        $this->_conexionBDAux->ejecutarSQL($sql);
        if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
          $total = $this->_conexionBDAux->obtenerFilaComoCadena();
        else
          $total = "0";
        $td_saldo_titan = $this->_html->tag("td", "class='celda_total_2 alineacion_centro' colspan='3'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));
      $tr_total_titan = $this->_html->tag("tr", "", array($td_label_titan,$td_saldo_titan));

      $td_label_saldo_final = $this->_html->tag("td", "class='celda_total_2'", array("<label>Saldo Final Titan</label>"));
      $td_saldo_final = $this->_html->tag("td", "class='celda_total_2 alineacion_centro' colspan='3'", array("<label>".$this->_html->colocarPuntoMiles($total - $this->_total_venta_fullcarga)."</label>"));
      $tr_saldo_final = $this->_html->tag("tr", "", array($td_label_saldo_final,$td_saldo_final));

      //Aprovecho y muestro tambien el saldo final de Tigo
        $td_label_tigo = $this->_html->tag("td", "class='celda_total_2'", array("<label>Saldo Inicial Tigo</label>"));
        $sql = "SELECT sti_saldo
                FROM pozettos_saldo_inicial_tigo
                WHERE sti_fecha = '$fecha'
                AND sti_vigente = 1
                LIMIT 1";
        $this->_conexionBDAux->ejecutarSQL($sql);
        if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
          $total_tigo = $this->_conexionBDAux->obtenerFilaComoCadena();
        else
          $total_tigo = "0";
        $td_saldo_tigo = $this->_html->tag("td", "class='celda_total_2 alineacion_centro' colspan='3'", array("<label>".$this->_html->colocarPuntoMiles($total_tigo)."</label>"));
      $tr_total_tigo = $this->_html->tag("tr", "", array($td_label_tigo,$td_saldo_tigo));

      $td_label_saldo_final_tigo = $this->_html->tag("td", "class='celda_total_2'", array("<label>Saldo Final Titan</label>"));
      $td_saldo_final_tigo = $this->_html->tag("td", "class='celda_total_2 alineacion_centro' colspan='3'", array("<label>".$this->_html->colocarPuntoMiles($total_tigo - $this->_total_venta_tigo)."</label>"));
      $tr_saldo_final_tigo = $this->_html->tag("tr", "", array($td_label_saldo_final_tigo,$td_saldo_final_tigo));

      $trs_titan = $tr_total_titan." ".$tr_saldo_final." ".$tr_total_tigo." ".$tr_saldo_final_tigo;
    }
    $tbody_resumen = $this->_html->tag("tbody", "", array($trs_servicios,$tr_subtotal,$tr_total,$trs_titan));
    return $thead_resumen." ".$tbody_resumen;
  }
  
  function generarBackupBD()
  {
    if(!$this->_crearDumpMYSQL()) return "no se pudo generar el DUMP";
    if(!$this->_crearZIP())  return "no se pudo generar el ZIP";
    if(!$this->_enviarCorreo()) return "no se pudo enviar el correo";
    return true;
  }
  
  function _crearDumpMYSQL()
  { 
    $filename = "../backups/backupPozettos.sql";  
    $usuario = "root"; 
    $passwd = "root"; 
    $bd="pozettos";
    // Funcion para exportar la base de datos
    //windows 
    $executa = "C:\\wamp\\bin\\mysql\\mysql5.1.36\\bin\\mysqldump.exe -u $usuario  --password=$passwd --opt $bd > $filename";
    //linux
//     $executa = "mysqldump -u $usuario --password=$passwd --opt $bd > $filename";
    system($executa, $resultado);
    if($resultado)
      return false;
    else
      return true;
  }
  
  function _crearZIP()
  {
    // se debe activar la propiedad de PHP:  zlib output compression
    $fecha = date("Y-m-d");
    $struct=array("pozettos[$fecha].sql"=> file_get_contents("../backups/backupPozettos.sql"));
    $namezip = "../backups/pozettos[$fecha].zip";
   	$ZipData = array(); 
  	$Dircont = array(); 
  	$DirFile = array();
  	$offseto = 0;		
  	while(list($file,$data)=each($struct))
  	{	$file= str_replace("\\", "/", $file);  
  	    $dir=explode("/",$file);
  		for($i=0; $i<sizeof($dir); $i++)if($dir[$i]=="")unset($dir[$i]);					
  		$num=count($dir); //Total de niveles
  		$ele=0;  		  //Nivel actual
  		$dirname="";	  //Nombre archivo o directorio
  		while(list($idx,$val)=each($dir))
  		{	$ty=(++$ele)==$num?true:false;
  			$ty=trim($data)!=""?$ty:false;//Compruebar si el ultimo elemento es directorio o archivo
  			$dirname.=$val.($ty?"":"/");
  			if(isset($DirFile[$dirname]))continue; else $DirFile[$dirname]=true;			
  			$gzdata="";				
  			if($ty)
  			{	$unziplen=strlen($data);  
  				$czip=crc32($data);  
  				$gzdata=gzcompress($data);  
  				$gzdata=substr(substr($gzdata,0,strlen($gzdata)-4),2); 
  				$cziplen=strlen($gzdata);  
  			}						
  			$ZipData[]="\x50\x4b\x03\x04".($ty?"\x14":"\x0a")."\x00\x00\x00".($ty?"\x08":"\x00")."\x00\x00\x00\x00\x00".
  					   pack("V",$ty?$czip:0).pack("V",$ty?$cziplen:0).pack("V",$ty?$unziplen:0).pack("v",strlen($dirname)). 
  					   pack("v",0).$dirname.$gzdata.pack("V",$ty?$czip:0).pack("V",$ty?$cziplen:0).pack("V",$ty?$unziplen:0);
  			$Dircont[]="\x50\x4b\x01\x02\x00\x00".($ty?"\x14":"\x0a")."\x00\x00\x00".($ty?"\x08":"\x00")."\x00\x00\x00\x00\x00".
  					   pack("V",$ty?$czip:0).pack("V",$ty?$cziplen:0).pack("V",$ty?$unziplen:0).pack("v",strlen($dirname)). 
  					   pack("v", 0 ).pack("v",0).pack("v",0).pack("v",0).pack("V",$ty?32:16).pack("V",$offseto).$dirname;  		
  			$offseto=strlen(implode("",$ZipData));			
  		}//Fin While dir		
  	}//Fin While archivos
  	$data = implode("",$ZipData);  
  	$cdir = implode("",$Dircont);  	
  	$data=$data.$cdir."\x50\x4b\x05\x06\x00\x00\x00\x00".pack("v",sizeof($Dircont)).pack("v",sizeof($Dircont)).pack("V",strlen($cdir)).pack("V",strlen($data))."\x00\x00";
    if($namezip)//Construir el archivo
    {	if(($fp=fopen($namezip,"wb")))
   		{	
        fwrite($fp,$data);
  			fclose ($fp);
  			return true;
		  }else return false;
    }else return $data;	   
  }

  function _enviarCorreo()
  {
    $fecha = date("Y-m-d");
    //  se debe activar la extension de php: php_openssl
    // example on using PHPMailer with GMAIL
    include("../herramientas/PHPMailer/class.phpmailer.php");
    include("../herramientas/PHPMailer/class.smtp.php"); // note, this is optional - gets called from main class if not already loaded
    $mail             = new PHPMailer();
    $mail->IsSMTP();
    $mail->SMTPAuth   = true;                  // enable SMTP authentication
    $mail->SMTPSecure = "ssl";                 // sets the prefix to the servier
    $mail->Host       = "smtp.gmail.com";      // sets GMAIL as the SMTP server
    $mail->Port       = 465;                   // set the SMTP port 
    $mail->Username   = "xxx";  // GMAIL username
    $mail->Password   = "xxx";            // GMAIL password
    $mail->From       = "xxx@gmail.com";
    $mail->FromName   = "Pozettos Server";
    $mail->Subject    = "Backup pozettos [$fecha]";
    $mail->AltBody    = "Backup de la base de datos Pozettos.net"; //Text Body
    $mail->MsgHTML("Backup de la base de datos Pozettos.net");
    $mail->AddAttachment("../backups/pozettos[$fecha].zip");             // attachment
    $mail->AddAddress("dadagama@gmail.com","Darwin");
    $mail->IsHTML(true); // send as HTML
    if(!$mail->Send())
    {
//       echo $mail->ErrorInfo;
      return false;
    }
    else
      return true;
  }
}
?>
