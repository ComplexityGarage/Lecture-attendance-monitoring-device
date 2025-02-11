<?php

use App\Http\Controllers\Api\CreateVisitController;
use App\Http\Controllers\Api\ResetVisitsController;
use Illuminate\Support\Facades\Route;

Route::post('/visitors', CreateVisitController::class)->name('visitors.new');

Route::middleware('auth')->group(function () {
    Route::post('/visitors/reset', ResetVisitsController::class)->name('visitors.reset');
});