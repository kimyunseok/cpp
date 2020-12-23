package com.inhamall.model;

public class Basket {
	private static final long serialVersionUID = 1L;

	private int basketidx;
	private String userid;
	private int productidx;
	private int qty;
	
	public int getBasketidx() {
		return basketidx;
	}
	public void setBasketidx(int basketidx) {
		this.basketidx = basketidx;
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
	
	
}
