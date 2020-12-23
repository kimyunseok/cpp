<%@page import="com.inhamall.dao.UserDao"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<link type="text/css" rel="stylesheet" href="style.css">
<title>회원가입</title>
</head>
<body>
	<header>
		<%@include file="layout/header.jsp"%>
	</header>

	<center>
		<form method="post" action="findIDPWGo.jsp" style="margin: 100px;">
		<br><br><br><br><br>
			<h1>회원가입 시에 입력했던 이메일과 연락처를 정확하게 입력해주세요.</h1><br>
			
			<input style="font-size: 25px" type="text" name="email" placeholder="E-Mail" maxlength="50" size="25"><p>
			
			<input style="font-size: 25px" type="text" name="contact" placeholder="Contact"
				maxlength="16" size="25"><br><br><br><br><br><br><br><br><br><br>
			 
			 <input type="submit" value="입력완료" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;">
			 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			 
			 <input type="reset" value="다시입력" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;">
			 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			 
			 <input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; font-size: 18px;"/>
			
		</form>
	<hr>

	<footer>
		<%@include file="layout/bottom.jsp"%><!-- footer.html 불러와서 사용(전페이지 공통) -->
	</footer>
</html>
