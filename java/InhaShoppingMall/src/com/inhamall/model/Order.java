package com.inhamall.model;

public class Order {
	private static final long serialVersionUID = 1L;
	

	private int orderidx;
	private String userid;
	private int productidx;
	private int qty;
	private String memo;
	
	public int getOrderidx() {
		return orderidx;
	}
	public void setOrderidx(int orderidx) {
		this.orderidx = orderidx;
	}
	public String getUserid() {
		return userid;
	}
	public void setUserid(String userid) {
		this.userid = userid;
	}
	public int getProductidx() {
		return productidx;
	}
	public void setProductidx(int productidx) {
		this.productidx = productidx;
	}
	public int getQty() {
		return qty;
	}
	public void setQty(int qty) {
		this.qty = qty;
	}
	public String getMemo() {
		return memo;
	}
	public void setMemo(String memo) {
		this.memo = memo;
	}
	
	
}
