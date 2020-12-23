<%@page import="com.inhamall.dao.UserDao"%>
<%@page import="com.inhamall.model.User"%>
<%@page import="java.util.ArrayList"%>
<%@page import="java.util.List"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>

<%@ page import="java.sql.*"%>

<%
	request.setCharacterEncoding("utf-8");
%>

<%
	String email = request.getParameter("email");
	String contact = request.getParameter("contact");
%>

<%
	UserDao dao = new UserDao();
	List<User> users = new ArrayList<User>();
	users = dao.getUserByEC(email, contact);
	String check = "";
	String img = "";
	try {
		if(users.size() > 0) {
			for(User user : users) {
			check += user.getUsername() + "님의 아이디는<br>" + user.getId()
			+ "<br>이고 <br>비밀번호는<br>" + user.getPassword() + "<br>입니다.<br><br>";
			}
			img = "image/ok.png";
		} else { check="회원님의 정보를 찾을 수 없습니다.<br>이메일과 연락처를 확인해 보세요."; img = "image/fail.png";}
	} catch (Exception e) {
		e.printStackTrace();
	}

%>
<center>
<h2><%=check %></h2>
<img alt="" src= <%=img %>> <br><br>

 <input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
 &nbsp;&nbsp;&nbsp;
 
 <input type="button" onclick="location.href='login.jsp'" value="로그인화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;"/>
  &nbsp;&nbsp;&nbsp;
  
 </center>