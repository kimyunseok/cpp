<%@page import="com.inhamall.dao.UserDao"%>
<%@ page language="java" contentType="text/html; charset=utf-8" 
pageEncoding="utf-8"%> 
<!DOCTYPE html> 
<html> 
<head> 
<meta charset="utf-8"> 
<title>ID 입력</title> 
<script src="https://code.jquery.com/jquery-3.5.1.js"></script> 
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css"> 
<script type="text/javascript">
function goUse(id) { 
	//전달받은 아이디를 오픈한 윈도우로 보내고 
	opener.document.getElementById('id').value = id;
	opener.document.getElementById('idoverLapText').innerHTML = "ID 사용가능!"
	opener.idok = true;
	if(opener.pwok == true) {
		opener.document.getElementById('submit').disabled = false;
		opener.document.getElementById('notice').innerHTML = ""
		opener.document.getElementById('submit').style.background = "black";
	} else {
		opener.document.getElementById('submit').disabled = true;
		opener.document.getElementById('notice').innerHTML = "비밀번호를 확인하세요."
		opener.document.getElementById('submit').style.background = "grey";
	}
	//현재윈도우는 닫는다 
	window.close(); 
	}
	
function cantUse() { 
	opener.document.getElementById('notice').innerHTML = "아이디가 중복입니다!<br> 다른 아이디를 입력해주세요!"
	opener.document.getElementById('idoverLapText').innerHTML = "아이디가 중복됩니다!"
	window.close(); 
	}
	</script>
	 
	</head> 
	<%
		//입력결과 
		String id=request.getParameter("id"); 
		UserDao dao = new UserDao();
		boolean flag=dao.searchId(id); 
		if(flag) { 
			//이미 아이디가 존재한다면 
			%>
			<center>
			<table> 
			<tr> 
			<td> <img alt="" src="image/not.png"> <br><b style="color: red; font-size: 25px"> 이미 존재하는 아이디입니다<br> 다른 아이디로 입력해주세요~</b> 
			<br><input type="button" value="확인" onclick="cantUse()" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; font-size: 18px;"> </td> 
			</tr> 
			</table> 
			</center>
			<%} 
		else {
		%> 
		<!-- 아이디가 없을경우 --> 
		<center>
		<table> 
		<tr> 
		<td> <img alt="" src="image/ok.png"> <br> <b style="color: green;  font-size: 25px"> 사용가능한 아이디입니다<br></b> 
		<input type="button" value="사용하기" onclick="goUse('<%=id%>')" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; font-size: 18px;"></td> 
		</tr> 
		</table>
		</center> 
		<%} 
		%> 
<body> 
</body> 
</html>