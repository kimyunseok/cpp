package com.inhamall.model;

import java.util.Date;

public class User {
	private static final long serialVersionUID = 1L;
	

	private int useridx;
	private int usertype; // 0 : 일반회원, 1 : 실버, 2 : 골드, 3 : 플레티넘, 4 : VIP, 5 : 운영진
	private String id;
	private String password;
	private String username;
	private String dob;
	private String sex;
	private String contact;
	private String postcode;
	private String roadaddress;
	private String jibunaddress;
	private String address;
	private String email;
	
	public int getUseridx() {
		return useridx;
	}
	public void setUseridx(int useridx) {
		this.useridx = useridx;
	}
	public int getUsertype() {
		return usertype;
	}
	public void setUsertype(int usertype) {
		this.usertype = usertype;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getDob() {
		return dob;
	}
	public void setDob(String dob) {
		this.dob = dob;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getContact() {
		return contact;
	}
	public void setContact(String contact) {
		this.contact = contact;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	
	@Override
	public String toString() {
		return "User [useridx=" + useridx + ", usertype=" + usertype + ", id=" + id + ", password=" + password
				+ ", username=" + username + ", dob=" + dob + ", sex=" + sex + ", contact=" + contact + ", address="
				+ address + ", email=" + email + "]";
	}
	
	
	
}
