<?php

use App\Http\Controllers\Api\CreateVisitController;
use Illuminate\Support\Facades\Route;

Route::post('/visitors', CreateVisitController::class)->name('visitors.new');