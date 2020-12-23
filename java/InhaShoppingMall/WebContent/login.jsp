<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<link type="text/css" rel="stylesheet" href="style.css">
<title>로그인</title>
</head>
<body>
	<header>
		<%@include file="layout/header.jsp"%><!-- header.html 불러와서 사용(전 페이지 공통) -->
	</header>
	<%@ include file="layout/menubar.html"%><!-- menubar.html 불러와서 사용(전 페이지 공통) -->
	<br>
	<br>
	<center>
		<form method="post" action="loginGo.jsp" style="margin: 100px;">
		<br><br><br>
			<h2>아이디</h2><input style="font-size: 25px" type="text" name="id" placeholder="ID" maxlength="50" size="25"><p>
			<h2>비밀번호</h2>
			<input style="font-size: 25px" type="password" name="passwd" placeholder="Password"
				maxlength="16" size="25"><br><br><br><br><br><br><br><br><br><br>
			 
			 <input type="submit" value="로그인" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
			 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			 
			 <input type="button" onclick="location.href='findIDPW.jsp'" value="아이디/ 비밀번호 찾기" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
			 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			 
			 <input type="button" onclick="location.href='signup.jsp'" value="회원가입" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; font-size: 18px;"/>
		
		</form>
	</center>
	<br>
	<br>
	<hr>

	<footer>
		<%@include file="layout/bottom.jsp"%><!-- footer.html 불러와서 사용(전페이지 공통) -->
	</footer>
	</body>
</html>